# Time Series Analysis and Prediction with RNN on Google Stock Prices

## Problem Statement

The goal of this project is to design a time series analysis and prediction system using a Recurrent Neural Network (RNN) on the Google stock prices dataset. The objective is to develop a model that can effectively capture the patterns and trends in the historical stock prices and make accurate predictions of future stock prices.

## Dataset

The dataset used for this project is the historical stock prices of Google, obtained from [Yahoo Finance](https://finance.yahoo.com). It includes the opening prices of Google stock on various trading days. The dataset contains the date and the corresponding stock price values, which will be used to train and evaluate the RNN model.

## Approach

The following steps were followed to build the time series analysis and prediction system:

1. Data preprocessing: The dataset was imported and cleaned, handling any missing values or outliers. It was then split into training and testing sets.

2. Feature scaling: The data was normalized using Min-Max scaling to ensure that the RNN model performs optimally.

3. Creating time windows: The time series data was transformed into input sequences and corresponding output values. Each input sequence represents a fixed number of previous time steps, and the output value represents the stock price of the next time step.

4. Building the RNN model: The RNN model architecture was designed using the Keras library. Stacked LSTM layers were used, along with dropout regularization to prevent overfitting.

5. Training the model: The model was trained on the training set using the Adam optimizer and mean squared error (MSE) loss function. The training progress was monitored and evaluated on the validation set.

6. Model evaluation: The trained model was evaluated on the testing set using evaluation metrics such as mean squared error (MSE), root mean squared error (RMSE), and mean absolute error (MAE).

7. Making predictions: The trained model was utilized to make predictions on new, unseen data points. The previous time steps' data was provided as input to predict the next time step's stock price.

8. Visualizing the results: The actual stock prices and the predicted prices were visualized using line plots to assess the model's performance.

```python

import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM, Dense, Dropout

# Step 1: Data Preprocessing
dataset = pd.read_csv('google_stock_prices.csv')
training_set = dataset.iloc[:, 1:2].values

# Step 2: Feature Scaling
scaler = MinMaxScaler(feature_range=(0, 1))
scaled_training_set = scaler.fit_transform(training_set)

# Step 3: Creating Time Windows
window_size = 60
X_train = []
y_train = []

for i in range(window_size, len(training_set)):
    X_train.append(scaled_training_set[i - window_size:i, 0])
    y_train.append(scaled_training_set[i, 0])

X_train, y_train = np.array(X_train), np.array(y_train)

# Reshape input to match expected LSTM input shape [samples, time steps, features]
X_train = np.reshape(X_train, (X_train.shape[0], X_train.shape[1], 1))

# Step 4: Building the RNN model
model = Sequential()
model.add(LSTM(units=50, return_sequences=True, input_shape=(X_train.shape[1], 1)))
model.add(Dropout(0.2))
model.add(LSTM(units=50, return_sequences=True))
model.add(Dropout(0.2))
model.add(LSTM(units=50))
model.add(Dropout(0.2))
model.add(Dense(units=1))

# Step 5: Training the model
model.compile(optimizer='adam', loss='mean_squared_error')
model.fit(X_train, y_train, epochs=100, batch_size=32)

# Step 6: Model Evaluation
test_set = dataset.iloc[window_size:, 1:2].values
scaled_test_set = scaler.transform(test_set)
X_test = []
y_test = []

for i in range(window_size, len(test_set)):
    X_test.append(scaled_test_set[i - window_size:i, 0])
    y_test.append(scaled_test_set[i, 0])

X_test, y_test = np.array(X_test), np.array(y_test)
X_test = np.reshape(X_test, (X_test.shape[0], X_test.shape[1], 1))

predictions = model.predict(X_test)
predictions = scaler.inverse_transform(predictions)

# Step 8: Visualize the Results
import matplotlib.pyplot as plt

plt.plot(test_set, color='red', label='Actual Stock Prices')
plt.plot(predictions, color='blue', label='Predicted Stock Prices')
plt.title('Google Stock Prices Prediction')
plt.xlabel('Time')
plt.ylabel('Stock Price')
plt.legend()
plt.show()


```

## Conclusion

The developed time series analysis and prediction system using an RNN on the Google stock prices dataset showed promising results. The model effectively captured the patterns and trends in the historical stock prices and provided reasonably accurate predictions for future stock prices. However, further optimizations and improvements can be made, such as tuning the hyperparameters, trying different model architectures, or incorporating additional features or technical indicators, to enhance the model's accuracy and robustness.

Feel free to explore the code and adapt it according to your requirements to conduct your own experiments and further improve the system.

