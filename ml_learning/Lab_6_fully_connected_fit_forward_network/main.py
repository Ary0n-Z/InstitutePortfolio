import numpy as np
from numpy.random import normal
import sklearn.datasets as ds
import matplotlib.pyplot as plt
from sklearn.utils import shuffle
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score

class FullyConnectedFitForwardNetwork:

    def __net_input(self,X,layer):
        return X.dot(self.W[layer]) + self.B[layer]
    
    def forward_pass(self,A):
        for layer in range(1,self.depth_ + 1):
            Z = self.__net_input(A,layer)
            A = self.activate_layer(Z,layer)
        return A
    
    def activate_layer(self,Z,layer):
        return self.activation_functions[layer](Z)

    def cost(self,X,y,regularization_rate):
        p = self.forward_pass(X)
        cross_entropy = -((y*np.log(p)) + (1-y)*np.log(1-p)).sum()
        l2_cost = 0
        for layer in range(1,self.depth_+1):
            l2_cost += (self.W[layer] ** 2).sum()
        l2_cost = - l2_cost * regularization_rate
        return cross_entropy + l2_cost
    
    def forward_pass_g(self,A,W,B):
        for layer in range(1,self.depth_ + 1):
            Z = A.dot(W[layer])+ B[layer]
            A = self.activate_layer(Z,layer)
        return A
    
    def cost_g(self,X,y,regularization_rate,TETA):
        W,B = TETA
        p = self.forward_pass_g(X,W,B)
        cross_entropy = -((y*np.log(p)) + (1-y)*np.log(1-p)).sum()
        l2_cost = 0
        for layer in range(1,self.depth_+1):
            l2_cost += (self.W[layer] ** 2).sum()
        l2_cost = - l2_cost * regularization_rate
        return cross_entropy + l2_cost
    
    def grad_check(self,X,y,l2_rate,dW,dB):
        TETA = [self.W.copy()] + [self.B.copy()]
        D_TETA = [dW] + [dB]
        deriv_num_TETA = []
        deriv_TETA = []
        for d,dd in zip(TETA,D_TETA):
            for layer in range(1,self.depth_+1):
                n,m = d[layer].shape
                for i in range(n):
                    for j in range(m):
                        tmp = d[layer][i,j]
                        d[layer][i,j] = tmp - 10e-7
                        c1 = self.cost_g(X,y,l2_rate,TETA)
                        d[layer][i,j] = tmp + 10e-7
                        c2 = self.cost_g(X,y,l2_rate,TETA)
                        deriv_num_TETA.append((c1-c2)/(2.0*10e-7))
                        d[layer][i,j] = tmp 
                        deriv_TETA.append(dd[layer][i,j])
        deriv_num_TETA = np.array(deriv_num_TETA)
        deriv_TETA = np.array(deriv_TETA)
        error = self.l2_norm(deriv_num_TETA - deriv_TETA)/(self.l2_norm(deriv_num_TETA) + self.l2_norm(deriv_TETA))
        return error < 10e-7
    def l2_norm(self,X):
        return (np.sum(X)**2)**0.5
    
    def __split_mini_batch(self,X,y,batch_count):
        n,_ = X.shape
        rX,ry = shuffle(X,y)
        if batch_count > n:
            batch_count = n
        rx = np.array_split(rX,batch_count)
        ry = np.array_split(ry,batch_count)
        return zip(rx,ry)
        
    def backward_pass(self,X,y,learning_rate,hidden_neurons,functions,max_iter,batch_count,eps = 0.01,l2_rate = 0.0):
        self.activation_functions = functions
        _,m = X.shape
        neurons = [m] + hidden_neurons + [1]
        self.W = {}; self.B = {}
        W = self.W; B = self.B
        for layer in range(1,len(neurons)):
            W[layer] = np.random.normal(scale = 0.01,size = (neurons[layer-1],neurons[layer]))
            B[layer] = np.random.normal(scale = 0.01,size = (1,neurons[layer]))
        A = {}; Z = {}; dA = {}; dZ = {}; dW = {}; db = {}
        self.depth_ = len(neurons) - 1; L = self.depth_
        it = 0
        current_cost = self.cost(X,y,l2_rate)
        while True:
            prev_cost = current_cost
            mini_batches = self.__split_mini_batch(X,y,batch_count)
            for X_b,y_b in mini_batches:
                # Step 1 - forward pass
                A[0] = X_b
                for layer in range(1,self.depth_ + 1):
                    Z[layer] = self.__net_input(A[layer-1],layer)
                    A[layer] = self.activate_layer(Z[layer],layer)
                # Step 2 - backward pass
                dA[L] = ((1.0 - y_b)/(1.0 - A[L]) - y_b/A[L])
                dZ[L] = dA[L] * functions[L](Z[L],True)
                dW[L] = (A[L - 1].T).dot(dZ[L]) + l2_rate *(W[L]**2)
                db[L] = np.mean(dZ[L],axis=0,keepdims = True)
                for layer in range(self.depth_-1,0,-1):
                    # 2.a 
                    dA[layer] = dZ[layer + 1].dot(W[layer + 1].T)
                    dZ[layer] = dA[layer] * functions[layer](Z[layer],True)
                    # 2.b
                    dW[layer] = (A[layer - 1].T).dot(dZ[layer]) + l2_rate *(W[layer]**2)
                    #dW[layer] = ((dZ[layer].T).dot(A[layer-1])).T
                    db[layer] = np.mean(dZ[layer],axis=0,keepdims = True)
                    # Step 3
                for layer in range(1,self.depth_+1):
                    W[layer] -= learning_rate * dW[layer]
                    B[layer] -= learning_rate * db[layer]
            it += 1
            if it == max_iter:
                break
            current_cost = self.cost(X,y,l2_rate)
            ceps = current_cost - prev_cost
            if abs(ceps) < eps:
                break
        self.it = it
        return self

def sigmoid(Z,deriv = False):
    if deriv:
        s = sigmoid(Z)
        return s*(1-s)
    s = 1.0/(1.0 + np.exp(-1.0 * Z))
    np.minimum(s, 1.0 - np.finfo(np.float64).eps,out=s)
    np.maximum(s, np.finfo(np.float64).eps,out=s)
    return s

def relu(Z, deriv = False):
    if deriv:
        return np.where(Z > 0, 1, 0)
    return np.where(Z > 0, Z, 0)

n_samples = 1000
variance = 1
samples_per_corner = int(n_samples/4)
y = np.array([1]*(2*samples_per_corner) + [0]*(2*samples_per_corner))
# left buttom
x1 = np.random.normal(3,variance,samples_per_corner)
x2 = np.random.normal(3,variance,samples_per_corner)
# right top
x1 = np.concatenate((x1, np.random.normal(9,variance,samples_per_corner)), axis=None)
x2 = np.concatenate((x2, np.random.normal(9,variance,samples_per_corner)), axis=None)
# right buttom
x1 = np.concatenate((x1, np.random.normal(9,variance,samples_per_corner)), axis=None)
x2 = np.concatenate((x2, np.random.normal(3,variance,samples_per_corner)), axis=None)
# left top
x1 = np.concatenate((x1, np.random.normal(3,variance,samples_per_corner)), axis=None)
x2 = np.concatenate((x2, np.random.normal(9,variance,samples_per_corner)), axis=None)

#X = np.stack((x1,x2),axis=0).T
#y_true = y.reshape(-1,1)
X = np.array([[0,1]])
y = np.array([[1]])
#X,y_true = shuffle(X,y_true)
#X = StandardScaler().fit_transform(X)

hidden_neurons = [4]
activations_f = {1:relu,2:sigmoid}
nn = FullyConnectedFitForwardNetwork()
np.random.seed(42)
nn.backward_pass(X,y,0.1,hidden_neurons,activations_f,50,50,eps=0.1,l2_rate=0.0)
y_p = np.where(nn.forward_pass(X) > 0.5,1,0)
print(accuracy_score(y,y_p),nn.it)
4+6
# X = np.array([[1,0],[0,1]])
# y = np.array([[1],[0]])
# nn.backward_pass(X,y,0.1,hidden_neurons,activations_f,d_activations_f)
# print( nn.forward_pass(X))