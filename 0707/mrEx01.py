import matplotlib.pylab as plt
from sklearn import linear_model

reg = linear_model.LinearRegression()

X = [[174],[152],[138],[128],[186]]
y = [71,55,46,38,88]

reg.fit(X,y)


print(reg.predict([[178]]))
plt.scatter(X,y,color="black")
plt.plot(X,reg.predict(X),color="blue",linewidth=3)
plt.show()


