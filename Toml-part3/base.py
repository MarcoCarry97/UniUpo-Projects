import pandas as pd
import numpy as np
import sklearn.metrics as skm
from sklearn.model_selection import train_test_split as datasetSplit
from sklearn.preprocessing import StandardScaler
import math
import dplotter as dp
from sklearn.model_selection import GridSearchCV as gridTuner

def calcNormalizedData(data):
    mean=np.mean(data);
    std=np.std(data);
    return (data-mean)/std

def addNormalizedData(data):
    data.insert(0,"normalizedO3",calcNormalizedData(data["Sensor_O3"].values))
    data.insert(0,"normalizedRefSt",calcNormalizedData(data["RefSt"].values))

def addTime(data):
    time=np.arange(0,len(data.values),1)
    data.insert(0, "time", time)
    
def changeDirection(data):
    return max(data)-data

def readData(filename,separator):
    data=pd.read_csv(filename,delimiter=separator)
    data.isnull().values.any()
    data=data.dropna()
    if("date" in data.keys()): #converting date string in datetime
        data["date"]=pd.to_datetime(data["date"]).dt.strftime('%Y-%m-%dT%H:%M')
    if("Sensor_O3" in data.keys()): #converting O3 value in floats
        nums=[]
        for n in data["Sensor_O3"]:
            if n.count(".")>1:
                n=n.replace(".","",1)
            nums+=[np.float64(n)*0.09]
        data["Sensor_O3"]=np.array(nums)
   # elif("RelHum" in data.keys()):
    #    data["RelHum"]=changeDirection(data["RelHum"])
    data.head()
    return data;

def mergeData(data,other,how,left,right):
    return pd.merge(data,other,how=how,left_on=left,right_on=right)

def printShape(features,data):
    print(features,data.shape)

def prepareData(listFileNames,separator):
    listdata=[]
    for filename in listFileNames: #Loading and preprocessing
        listdata+=[readData(filename,separator)]
    data=listdata[0]
    for i in range(1,len(listdata)): #Merging
        data=mergeData(data,listdata[i],"inner","date","date")
        data.head()
    return data      

def removeEquals(features,subsets):
    for i in (1,len(features)):
        sub=[s for s in subsets if len(s)==i]
        for s1 in sub:
            for s2 in sub:
                i

def subsets(features):
    subsets=list()
    for feature in features:
        subsets+=[[feature]]
    for feature in features:
        for subset in subsets:
            if feature not in subset:
                other=subset+[feature]
                if(subset+[feature] not in subsets and
                   [feature]+subset not in subsets and
                   reversed(other) not in subsets):
                    subsets+=[other]
    return subsets
            

class Algorithm:
    def __init__(self,data,percentual,predictLabel,alpha=1,scale=False):
        parts=datasetSplit(data,data[predictLabel],train_size=percentual,random_state=1)
        self.trainingSet=parts[0]
        self.testSet=parts[1]
        self.trainingLabels=parts[2]
        self.testLabels=parts[3]
        self.trainingSet=self.trainingSet.drop([predictLabel],axis=1)
        self.testSet=self.testSet.drop([predictLabel],axis=1)
        if(scale):
            scale=StandardScaler()
            self.trainingSet=scale.fit_transform(self.trainingSet)
            self.testSet=scale.fit_transform(self.testSet)
        self.predictLabel=predictLabel
        self.modelType="Normal"
        self.alpha=alpha  

    def makeModel(features=[]):
        pass
    
    def useRidgeRegression(self):
        self.modelType="Ridge"
        
    def useLasso(self):
        self.modelType="Lasso"
        
    def noRegularization(self):
        self.modelType="Normal"

    def forwardSelection2(self):
        subs=subsets(list(self.trainingSet.columns))
        best=[]
        bestR2=0
        bestRmse=0
        first=True
        for s in subs:
            model=self.makeModel(features=s)
            #model.tune()
            res=model.predict()
            if(first):
                best=s
                bestR2=res.rsquare
                bestRmse=res.rmse
                first=False
            if(bestR2<res.rsquare):
                best=s
                bestR2=res.rsquare
                bestRmse=res.rmse
            print(s,res.rsquare,res.rmse)
        print("best:",best,bestR2,bestRmse)
        return best

    def forwardSelection(self):
        availableFeatures=list(self.trainingSet.columns)
        numColumns=len(self.trainingSet)
        numAvailableFeatures=numColumns
        basePerf=-9999
        bestSubSet=[]
        while numAvailableFeatures>0:
            bestPerf=-9999
            bestFeature=None
            for i in range(0, len(availableFeatures)):
                feature=availableFeatures[i]
                s=bestSubSet+[feature]
                model=self.makeModel(features=s)
                res=model.predict()
                curPerf=res.rsquare
                if(curPerf>bestPerf):
                    bestPerf=curPerf
                    bestFeature=feature   
            if(bestPerf>basePerf):
                basePerf=bestPerf
                bestSubSet+=[bestFeature]
                availableFeatures.remove(bestFeature)
                numAvailableFeatures-=1
            else:
                break;
        return bestSubSet
        
    


class Model:
    def __init__(self,trainingSet,trainingLabels,testSet,testLabels,modelType="Normal",alpha=1,selectedLabels=[]):
        self.trainingSet=trainingSet
        self.testSet=testSet
        self.trainingLabels=trainingLabels
        self.testLabels=testLabels
        self.alpha=alpha
        self.ridge=False
        self.none=True
        self.model=None
        self.features=None
        self.selectedLabels=selectedLabels
        
    def getCoefficients(self):
        return self.model.coef_
    
    def getIntercept(self):
        return self.model.intercept_
    
    def predict(self):
        prediction=self.model.predict(self.testSet)
        truevalue=self.testLabels
        return self.getResults(prediction,truevalue)
    
    def redefineSets(self):
        if(len(self.selectedLabels)>0):
            self.trainingSet=self.trainingSet[self.selectedLabels]
            self.testSet=self.testSet[self.selectedLabels]
    
    def getResults(self,prediction,actual):
        dt=pd.DataFrame({"prediction":prediction,self.trainingLabels.name:actual})
        score=self.model.score(self.testSet,actual)
        rsquare=skm.r2_score(actual, prediction)
        rmse=math.sqrt(skm.mean_squared_error(actual,prediction))
        mae=skm.mean_absolute_error(actual,prediction)
        #prob=self.model.predict_proba(self.testSet)
        return Results(dt,score,rsquare,rmse,mae)        
    
    def predictFromModel(self):
        intercept=self.model.intercept_
        coeff=self.model.coef_
        acc=intercept
        labels=self.testSet.columns
        for i in range(0,len(labels)):
            acc+=coeff[i]*self.testSet[labels[i]]
        return acc
            
    
    def plot(self,a,b):
        data=self.predict().prediction
        #data=pd.DataFrame({"prediction":preds,label:self.trainingLabels})
        #label=self.trainingLabels.name
        addTime(data)
        #data.insert(0, other, self.testSet[other].values)
        label=self.testLabels.name
        x="time"
        y=["prediction",label]
        title="predictions - "+label+" on time"
        dp.lineplot(data.iloc[a:b], x,y,title ,False,True)
       # dp.qqplot(data,"prediction","RefSt","qqplot-prediction-RefSt",False,True)
        
    def params(self):
        pass
        
    def tune(self):
        grid=gridTuner(self.model,self.params(),)
        grid.fit(self.trainingSet, self.trainingLabels)
        self.model=grid.best_estimator_
        print(grid.best_params_)
        
        
    
    
        
        
    
class Results:
    def __init__(self,prediction,score,rsquare,rmse,mae):
        self.prediction=prediction;
       # self.probability=prob
        self.score=score
        self.rsquare=rsquare
        self.rmse=rmse
        self.mae=mae
        
    def printRes(self):
        print("prediction: \n",self.prediction)
       # print("probability: ",self.probability)
        print("score: ",self.score)
        print("rsquare: ",self.rsquare)
        print("rmse: ",self.rmse)
        print("mae: ",self.mae)
    
 