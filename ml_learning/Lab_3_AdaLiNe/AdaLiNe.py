import numpy as np
import time

class AdaLiNe:
    def __init__(self):
        self.__activator = self.__reapeater
        self.__quantizer = self.__unit_step
        self.fit = self.__delta_rule

    def predict(self,X):
        return self.__quantizer(self.__activator(self.__net_input(X)))

    def __net_input(self,X):
        return X.dot(self.__weights) + self.__bias
    
    def __reapeater(self,X):
        return X
    
    def __unit_step(self,X):
        return np.where(X < 0, -1, 1)
    
    def get_params(self):
        return (self.__bias,self.__weights.copy())
    
    def __params_init(self,params_count,init_method):
        if init_method == 'rnd':
            self.__weights = np.random.normal(loc=0.0,scale=0.2,size=(params_count,1))
            self.__bias =  np.random.normal(loc=0.0,scale=0.2)
        else:
            self.__weights = np.zeros((params_count,1))
            self.__bias =0

    # X - matrix that represents train samples
    # y - lables for train samples
    # a - learning rate
    def __delta_rule(self,X,y,a):
        i = 0
        (n,m)=X.shape
        e = np.ones(shape=(1,n))
        self.__params_init(m,'rnd')
        while i < 10:
            error = (y - self.predict(X))
            delta_weights = a * (X.T).dot(error)
            delta_bias = a * e.dot(error)
            self.__weights += delta_weights
            self.__bias += delta_bias
            i+=1

def accuracy(labels,prediction):
   (n,_)=labels.shape
   correct =  np.count_nonzero((labels - prediction) == 0)
   return correct/n * 100

def preprocess_data(df_X):
    df_X.sort_values(by=['class'])
    df_X = df_X[:100]
    dictionary = {'class' : dict(zip(df_X['class'].unique(),[-1,1]))}
    return df_X.replace(dictionary)
    
import pandas as pd

df_X = preprocess_data(pd.read_csv('iris.csv'))
data_size = len(df_X)
test_count = int(data_size*0.8)
df_X_test = df_X.sample(test_count)
df_X_target = df_X.sample(data_size - test_count)

neuron = AdaLiNe()
X = df_X_test.values[:,:4]
y = df_X_test['class'].values.reshape((-1,1))

neuron.fit(X,y,0.001)
prediction = neuron.predict(X)
X_target = df_X_target.values[:,:4]
prediction = neuron.predict(X_target)
prediction