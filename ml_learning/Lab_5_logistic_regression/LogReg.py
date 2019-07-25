import numpy as np

class LogisticRegressionPrototype:
    def __init__(self,threshold = 0.5, tol = 1e-4, iter_max = 100):
        self.__threshold = threshold
        self.__tol = tol
        self.__iter_max = iter_max

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

    def fit(self,X,y_true,learning_rate):
        (_,m) = X.shape
        it = 0
        # step 1
        self.coef_ = np.random.normal(scale = 0.1, size = (m,1))
        self.intercept_ = np.random.normal(scale = 0.1)
        while True:
            # step 2
            for x,y in zip(X,y_true):
                # step 2.1
                y_p = self.__sigmoid(self.__net_input(x))
                # step 2.1
                error = (y - y_p).reshape((1,1))
                d_intercept = learning_rate * error.sum()
                x_T = x.reshape((m,1))
                d_coef = learning_rate * np.dot(x_T,error)
                # step 2.3
                self.coef_ += d_coef
                self.intercept_ += d_intercept
            # step 3
            it += 1
            if it == self.__iter_max:
                break
        return self
