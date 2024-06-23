# background parameters
import numpy as np
from scipy.integrate import quad
from scipy.special import erfinv



class linear:
    def __init__(self, intercept, slope, lolimit, hilimit):
        self.intercept = intercept
        self.slope = slope
        
        self.lolimit = lolimit
        self.hilimit = hilimit

        self.mass = []
        self.maxval = self.evaluate(self.lolimit if self.slope <= 0 else self.hilimit)

    def evaluate(self, t):
        return self.intercept + self.slope*t


    def next(self):        
        doLoop = True
        while (doLoop):
            # start with uniform random number in [lolimit , hilimit)
            x = np.random.uniform(self.lolimit, self.hilimit)
            y1 = self.evaluate(x)
            y2 = np.random.uniform(0, self.maxval)

            if (y2 < y1):
                filtered_x = x
                self.mass.append(filtered_x)
                return filtered_x
                


class gaussian:
    def __init__(self, mean, sigma):
        self.mean = mean
        self.sigma = sigma


    def next(self):
        return np.random.normal(self.mean, self.sigma)


    def evaluate(self, x):
        return (1/(self.sigma*np.sqrt(2.*np.pi)))*np.exp(-(x-self.mean)**2/(2*(self.sigma**2)))


    def integral(self, lolimit, hilimit):
        return quad(self.evaluate, lolimit, hilimit)[0]

    
    def inv_integral(self, lolimit, hilimit):
        return erfinv(1 - self.integral(lolimit, hilimit))*np.sqrt(2)
        


class signalWithBackground:
    def __init__(self, mean, sigma, sig_fraction, intercept, slope, XMIN, XMAX):
        self.sig_fraction = sig_fraction
        
        # Initalise classes
        self.signal = gaussian(mean, sigma)
        self.background = linear(intercept, slope, XMIN, XMAX)
        
        self.mass_sig = []
        self.mass_bgd = []
        self.mass = []


    # Draw random number form distribution
    def next(self):
        q = np.random.uniform()

        if (q < self.sig_fraction):
            # if here , we will draw x from signal distribution
            filtered_x = self.signal.next()
            self.mass_sig.append(filtered_x)
        else:
            # if here , we will draw x from background distribuion
            filtered_x = self.background.next()
            self.mass_bgd.append(filtered_x)
            
        self.mass.append(filtered_x)
        return filtered_x
