import numpy as np
import sklearn
import pandas as pd
from sklearn.model_selection import train_test_split
from numpy.linalg import inv
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import StandardScaler

class linear_regression:
    def __init__(self):
        self.__params = None
        self.__scaler = StandardScaler()

    def fit(self,X,y):
        X_std = self.__scaler.fit_transform(X)
        X_std_T = X_std.T
        A = X_std_T.dot(X)
        b = X_std_T.dot(y)
        self.__params = (inv(A)).dot(b)
        return self

    def predict(self,X):
        return self.__scaler.transform(X).dot(self.__params)

    def score(self,X, y):
        y_predict = self.__scaler.transform(X).dot(self.__params)
        u = ((y - y_predict)**2).sum()
        v = ((y - y_predict.mean())**2).sum()
        return (1-u/v)

    def get_params(self):
        return self.__params.copy()

dummy_var = False

headers = ['vendor','myct','mmin','mmax','cach','chmin','chmax','prp','erp']
df = pd.read_csv('machine.data',index_col=1,sep=',',header=None,names=headers)
(n,m) = df.shape
print('Has \'None\' = ',df.isin(['None']).any(axis=None))
y_true = df['prp'].values
df.drop(columns=['prp','erp'],inplace=True)
#dummy var for vendor
if dummy_var:
    df = pd.concat([df,pd.get_dummies(df['vendor'])],axis=1)
df.drop(columns=['vendor'],inplace=True)
df.insert(loc=0, column='ones', value=np.ones((n,1)))

y_true = y_true.reshape((n,1))
X=df.values

# test { train|validate } samples split 80:10:10
X_train,X_test,y_train,y_test = train_test_split(X, y_true, test_size=0.20, random_state=1)
X_valid,X_test,y_valid,y_test = train_test_split(X_test, y_test, test_size=0.50, random_state=1)

mylr = linear_regression().fit(X_train,y_train)
lr = LinearRegression().fit(X_train,y_train)
mylr.score(X_train,y_train)
lr.score(X_train,y_train)