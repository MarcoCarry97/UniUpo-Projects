import matplotlib.pyplot as plt
import numpy as np

class Plot:
    def __init__(self,limits):
        self.limits=limits

    def show(self,funs):
        lim=self.limits
        x=np.linspace(lim[0],lim[1],lim[2])
        fig=plt.figure()
        ax=fig.add_subplot(lim[0],lim[1],lim[2])
        ax.spines['left'].set_position('center')
        ax.spines['bottom'].set_position('center')
        ax.spines['right'].set_color('none')
        ax.spines['top'].set_color('none')
        ax.xaxis.set_ticks_position('bottom')
        ax.yaxis.set_ticks_position('left')
        for i in range(0,len(funs)):
            plt.plot(x,funs[i](x),"r")
        plt.show()