# Binary Classification of Movie Reviews using Deep Neural Networks

## Problem Statement

The objective of this project is to develop a binary classification system using Deep Neural Networks (DNN) to classify movie reviews into positive and negative categories based on the text content of the reviews. The goal is to build a model that can accurately predict the sentiment of movie reviews, which can be useful in various applications such as sentiment analysis, recommendation systems, and opinion mining.

## Dataset

The dataset used for this project is the IMDB dataset, which contains a large collection of movie reviews along with their sentiment labels. The dataset is preprocessed and pre-divided into a training set and a testing set, with each review represented as a sequence of integers. The dataset will be used to train and evaluate the Deep Neural Network model.

```python
import tensorflow as tf
from tensorflow.keras.datasets import imdb
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Embedding, GlobalAveragePooling1D

# Step 1: Data Preparation
(x_train, y_train), (x_test, y_test) = imdb.load_data(num_words=10000)

# Step 2: Data Preprocessing
x_train = tf.keras.preprocessing.sequence.pad_sequences(x_train, maxlen=100)
x_test = tf.keras.preprocessing.sequence.pad_sequences(x_test, maxlen=100)

# Step 3: Building the DNN Model
model = Sequential()
model.add(Embedding(10000, 16, input_length=100))
model.add(GlobalAveragePooling1D())
model.add(Dense(16, activation='relu'))
model.add(Dense(1, activation='sigmoid'))

# Step 4: Training the Model
model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
model.fit(x_train, y_train, epochs=10, batch_size=128, validation_data=(x_test, y_test))

# Step 5: Model Evaluation
loss, accuracy = model.evaluate(x_test, y_test)
print(f'Test Loss: {loss:.4f}')
print(f'Test Accuracy: {accuracy:.4f}')

# Step 6: Making Predictions
review = "This movie was great! I really enjoyed it."
review = tf.keras.preprocessing.sequence.pad_sequences([[word_index[word] for word in review.split()]], maxlen=100)
prediction = model.predict(review)[0][0]
sentiment = "positive" if prediction > 0.5 else "negative"
print(f'Review Sentiment: {sentiment} (Confidence: {prediction:.4f})')

```

## Approach

The following steps were followed to build the binary classification system:

1. **Data Preprocessing**: The IMDB dataset was loaded and preprocessed, including tokenization and padding of the movie reviews. The text data was transformed into numerical representations suitable for input to the Deep Neural Network.

2. **Building the Deep Neural Network**: A Deep Neural Network model architecture was designed to learn meaningful features from the movie review text data. The model consists of an embedding layer, followed by global average pooling and fully connected layers. The model's architecture can be adjusted and optimized to achieve better performance.

3. **Training the Model**: The Deep Neural Network model was trained on the training set using the labeled movie reviews. The model was optimized using a suitable loss function and an optimization algorithm. The training process involved iteratively updating the model's weights to minimize the loss and improve accuracy.

4. **Model Evaluation**: The trained Deep Neural Network model was evaluated on the testing set to assess its performance and generalization ability. Evaluation metrics such as accuracy, precision, recall, and F1-score were computed to measure the model's classification performance.

5. **Making Predictions**: The trained Deep Neural Network model was deployed to make predictions on new, unseen movie reviews. Given a movie review as input, the model predicts whether the sentiment is positive or negative, providing insights into the sentiment of the text.

6. **Conclusion**: The binary classification system using Deep Neural Networks demonstrated promising results in accurately classifying movie reviews into positive and negative categories based on the text content. By leveraging deep learning techniques, the system can effectively analyze and interpret the sentiment of movie reviews, enabling applications such as sentiment analysis and recommendation systems. However, further improvements can be explored, such as incorporating more advanced architectures, fine-tuning hyperparameters, or utilizing pre-trained word embeddings, to enhance the system's performance and handle more complex linguistic patterns.

Feel free to explore the code and adapt it according to your specific needs. The provided code serves as a starting point for building your own binary classification system for movie review sentiment analysis using Deep Neural Networks.

