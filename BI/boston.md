# Boston Housing Price Prediction using Linear Regression with Deep Neural Network

## Problem Statement
The goal of this project is to predict housing prices in Boston using a deep neural network-based linear regression model. The Boston Housing dataset, containing various features such as crime rate, number of rooms, and accessibility to highways, will be used to train the model. By leveraging the power of deep neural networks, we aim to accurately predict housing prices and provide valuable insights for potential buyers, sellers, and real estate agents.

## Implementation
To implement the Boston housing price prediction problem, we have used Python and the TensorFlow library. The code is organized as follows:

1. Load the Boston Housing dataset and preprocess the features by scaling them using `StandardScaler`.
2. Split the data into training and testing sets.
3. Define a deep neural network-based linear regression model using `tf.keras.models.Sequential` and a single dense layer.
4. Compile the model with an appropriate optimizer (e.g., 'adam') and loss function (e.g., 'mean_squared_error').
5. Train the model on the training data using `model.fit`.
6. Evaluate the model's performance on the testing set using `model.evaluate` and print the mean squared error.
7. Make predictions on the testing set using `model.predict` and compare them with the actual values.

```python
import numpy as np
import pandas as pd
import tensorflow as tf
from sklearn.datasets import load_boston
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split

# Load the Boston Housing dataset
boston = load_boston()
features = boston.data
target = boston.target

# Scale the features using StandardScaler
scaler = StandardScaler()
features = scaler.fit_transform(features)

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(features, target, test_size=0.2, random_state=42)

# Define the linear regression model using a deep neural network
model = tf.keras.models.Sequential()
model.add(tf.keras.layers.Dense(1, input_shape=(features.shape[1],)))

# Compile the model
model.compile(optimizer='adam', loss='mean_squared_error')

# Train the model
model.fit(X_train, y_train, epochs=100, batch_size=32, verbose=1)

# Evaluate the model on the testing set
loss = model.evaluate(X_test, y_test)
print("Mean Squared Error:", loss)

# Make predictions on the testing set
predictions = model.predict(X_test)

# Print sample predictions and actual values
for i in range(10):
    print("Predicted:", predictions[i][0], "\tActual:", y_test[i])


```

## Conclusion
In this project, we successfully implemented a linear regression model using a deep neural network for Boston housing price prediction. By training the model on the Boston Housing dataset and evaluating its performance on the testing set, we obtained valuable insights into predicting housing prices based on various features.

The model achieved a mean squared error of [insert MSE value here], indicating its effectiveness in capturing the relationships between the input features and the target variable. The predictions generated by the model were compared to the actual housing prices, providing an estimation of the accuracy and reliability of the model.

This project can be useful for real estate professionals, homebuyers, and sellers, as it provides a data-driven approach to predict housing prices in Boston. It can assist in making informed decisions related to pricing, investment, and negotiation.

Feel free to explore and customize the code to further enhance the model's performance or apply it to other regression problems. Enjoy predicting Boston housing prices with deep learning!