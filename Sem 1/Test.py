import numpy as np
import matplotlib.pyplot as plt
#from scipy.integrate import quad
from iminuit import Minuit

class linear:
    def __init__(self, intercept, slope, lolimit, hilimit):
        self.intercept = intercept
        self.slope = slope
        
        self.lolimit = lolimit
        self.hilimit = hilimit

        self.mass = []
        self.maxval = self.evaluate(self.lolimit if self.slope < 0. else self.hilimit)
       
    def evaluate(self, x):
        return self.intercept + self.slope*x
    

def min_chi2(intercept, slope):
    # Defined a Minuit specific funtion for chi^2 minimisation
    # for null Hypothesis only, therefore set with flat + guassian model
    
    model = linear(intercept, slope, np.min(x), np.max(x))

    N_exp = np.array(model.evaluate(x))
    #N_exp[N_exp <= 0.] = 1e-3

    #print(y, N_exp, np.log(y/N_exp))
    return (2*np.sum(N_exp - y + (y*np.log(y/N_exp))))


x = np.arange(0, 10, 1)
y = np.arange(0, 10, 1)

plt.plot(x, y)
plt.show()

startvals_H1 = {
        'intercept': 5.,
        'slope': 2,
    }


Min = Minuit(min_chi2, **startvals_H1)
Min.hesse()
Min.migrad()