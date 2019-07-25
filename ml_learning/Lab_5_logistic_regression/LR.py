import numpy as np
class LogisticRegressionPrototype:
    def __init__(self,threshold = 0.5, tol = 1e-4):
        self.__threshold = threshold
        self.__tol = tol

    def predict(self,X):
        return self.__activator(X).ravel()

    def __activator(self,X):
        return self.__quantizor(self.__sigmoid(self.__net_input(X)))

    def __net_input(self, X):
        return np.dot(X,self.coef_) + self.intercept_

    def __sigmoid(self, net_input):
        return 1.0/(1.0 + np.exp(-net_input))

    def __quantizor(self, positive_propability):
        return np.where(positive_propability > self.__threshold, 1, 0)
    def cost(self,X):
        c = 1
        y = self.predict(X)
        for xi,yi in zip(X,y):
            xi = xi.reshape(1,2)
            tmp = self.__sigmoid(self.__net_input(xi))
            c *= (tmp**yi) * (1 - tmp)**(1-yi)
        return c
    
    def fit(self,X,y_true,learning_rate):
        (n,m) = X.shape
        it = 0
        self.coef_ = np.random.normal(scale = 0.1, size = (m,1))
        self.intercept_ = np.random.normal(scale = 0.1)
        prev_cost = 10**5
        current_cost = self.cost(X) 
        while it < 100:
            prev_cost = current_cost
            i = np.random.randint(0, n)
            xi = X[i]
            yi = y_true[i]
            y_p = self.__sigmoid(self.intercept_ + (self.coef_*xi.reshape(m,1)).sum())
            error = yi - y_p
            d_intercept = learning_rate * error
            d_coef = learning_rate * xi.reshape(m,1) * error
            self.coef_ += d_coef
            self.intercept_ += d_intercept
            current_cost = self.cost(X)
            it+=1
        self.coef_ = self.coef_.reshape(m,1)
        return self