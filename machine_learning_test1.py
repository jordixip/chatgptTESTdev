from sklearn.linear_model import LinearRegression
from sklearn.datasets import load_boston

# Load the boston housing dataset
boston_data = load_boston()
X = boston_data.data
y = boston_data.target

# Create a linear regression model
model = LinearRegression()

# Fit the model to the data
model.fit(X, y)

# Make predictions
predictions = model.predict(X)
