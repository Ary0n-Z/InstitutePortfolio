import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn.utils import shuffle
from sklearn.metrics import accuracy_score

class LogisticRegression_:
    def __init__(self,threshold = 0.5, tol = 1e-3):
        self.__threshold = threshold
        self.__tol = tol

    def predict(self,X):
        return self.__quantizer(self.__activator(X))

    def __activator(self,X):
        return self.__sigmoid(self.__net_input(X))

    def __net_input(self, X):
        return np.dot(X,self.coef_) + self.intercept_

    def __sigmoid(self, net_input):
        return 1.0/(1.0 + np.exp(-net_input))

    def __quantizer(self, positive_propability):
        return np.where(positive_propability > self.__threshold, 1, 0)
    
    def cost(self,X):
        c = 1
        y = self.predict(X)
        for xi,yi in zip(X,y):
            xi = xi.reshape(1,2)
            tmp = self.__sigmoid(self.__net_input(xi))
            c *= (tmp**yi) * (1 - tmp)**(1-yi)
        return c
    
    def __split_mini_batch(self,X,y,batch_size):
        rX,ry = shuffle(X,y)
        rx = np.split(rX,batch_size)
        ry = np.split(ry,batch_size)
        return zip(rx,ry)
        
    def fit(self,X,y_true,learning_rate,batch_size):
        it = 0
        y_true = y_true.reshape((-1,1))
        (n,m) = X.shape
        self.coef_ = np.random.normal(scale = 0.1, size = (m,1))
        self.intercept_ = np.random.normal(scale = 0.1)
        while it < 1000:
            Mini_batches = self.__split_mini_batch(X,y_true,batch_size)
            for Xi,yi in Mini_batches:
                y_p = self.__activator(Xi)
                error = yi - y_p
                d_intercept = learning_rate * error.sum()
                d_coef = learning_rate * (Xi.T).dot(error)
                self.coef_ += d_coef
                self.intercept_ += d_intercept
            it+=1
        return self

log_reg = LogisticRegression_()

attributes = ['1','2','3','4','5','6','7','8','9','10','11','12','13','class']
df = pd.read_csv('data/heart.csv',sep=' ',header=None,names=attributes)
y = df['class'].values
X = df.drop(columns = 'class').values
df['class'].replace(2,0,inplace=True)
df.head()

X_train,X_validation,y_train,y_validation = train_test_split(X,y,test_size = 0.2)
y_train_prediction = log_reg.fit(X_train,y_train,0.01,8).predict(X_train)
print(accuracy_score(y_train,y_train_prediction.ravel()))
print(accuracy_score(y_validation,log_reg.predict(X_validation)))