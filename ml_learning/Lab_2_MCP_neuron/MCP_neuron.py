import numpy as np
import time

class MCP_neuron:
    def __init__(self):
        self.__activization = self.__unit_step_function

    def predict(self,X):
        return self.__activization(self.__net_input(X))

    def __net_input(self,X):
        return X.dot(self.__weights) + self.__bias
    
    def __unit_step_function(self,net_input):
        return np.where(net_input < 0, -1, 1)

    def get_params(self):
        return (self.__bias,self.__weights.copy())
    
    def __params_init(self,m,setting):
        if setting == 'rnd':
            self.__weights = np.random.normal(loc=0.0,scale=0.2,size=(m,1))
            self.__bias =  np.random.normal(loc=0.0,scale=0.2)
        else:
            self.__weights = np.zeros((m,1))
            self.__bias =0

    def rosenblatt_learning(self,X,y,learning_rate,param_init_setting='zeros',max_iter = 10):
        (_,m) = X.shape
        self.__params_init(m,param_init_setting)
        iteration_count = 0
        train = True
        while iteration_count < max_iter and train:
            prev_bias = self.__bias
            prev_weights = self.__weights.copy()
            for xi,yi in zip(X,y):
                prediction = self.predict(xi)
                error = yi - prediction
                delta_bias = learning_rate * error
                delta_weights = (learning_rate * error * xi).reshape(-1,1)
                self.__bias += delta_bias
                self.__weights += delta_weights
            if (self.__bias == prev_bias) and (prev_weights == self.__weights).all():
                train = False
            iteration_count +=1
        print('Iterations passed : {0}'.format(iteration_count))

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
# df_X_c1 = df_X[df_X['class']==1] #class 1
# df_X_c2 = df_X[df_X['class']==-1] #class 2

# # calculating of target and training samples proportion 20:80
# test_count_c1 = int(len(df_X_c1)*0.8)
# test_count_c2 = int(len(df_X_c2)*0.8)
# # create samples according to the proportions
# #select first 80%
# df_X_test_c1 = df_X_c1.iloc[:test_count_c1,:]
# df_X_test_c2 = df_X_c2.iloc[:test_count_c2,:]
# df_X_test = pd.concat([df_X_test_c1,df_X_test_c2],ignore_index = True)
# #target samples last 20%
# df_X_target_c1 = df_X_c1.iloc[test_count_c1:,:]
# df_X_target_c2 = df_X_c2.iloc[test_count_c2:,:]
# df_X_target = pd.concat([df_X_target_c1,df_X_target_c2],ignore_index = True)

neuron = MCP_neuron()
X = df_X_test.values[:,:4]
y = df_X_test['class'].values.reshape((-1,1))

neuron.rosenblatt_learning(X,y,0.1)
prediction = neuron.predict(X)
accuracy(np.array([[1,1,1,1,-1,-1,-1,-1]]).T,np.array([[1,1,-1,1,-1,-1,1,1]]).T)
# X_target["labels"] = result_labels.T
# accuracy(X_target[["class","labels"]])

# import matplotlib.pyplot as plt
# import seaborn as sns

# (bias,weights)=neuron.get_params()
# sns.scatterplot(x="sepal length", y="sepal width", hue="labels",data=X_target)
# min_x = X_target['sepal length'].min()
# max_x = X_target['sepal length'].max()

# slope = -(bias / weights.item(1))/(bias/weights.item(0))
# intercept = -bias / weights.item(1)
# decision_boundary = lambda x : ((slope*x) + intercept)

# X_plot = np.linspace(min_x, max_x)
# Y_plot = decision_boundary(X_plot)

# plt.plot(X_plot, Y_plot, linestyle=':')
# plt.show()
