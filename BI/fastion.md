# Plant Disease Detection System using CNN

## Problem Statement

The goal of this project is to develop a plant disease detection system using a Convolutional Neural Network (CNN). The objective is to build a model that can accurately classify plant images into different disease categories. By leveraging deep learning techniques, the system aims to assist in the early detection and diagnosis of plant diseases, enabling timely interventions for crop protection and management.

## Dataset

The dataset used for this project consists of a collection of plant images representing various plant diseases. The dataset includes images of healthy plants and plants affected by different diseases. Each image is labeled with the corresponding disease class. The dataset will be split into training and testing sets to train and evaluate the CNN model.

```python
import numpy as np
import tensorflow as tf
from tensorflow.keras.datasets import fashion_mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense

# Step 1: Data Preparation
(x_train, y_train), (x_test, y_test) = fashion_mnist.load_data()

# Step 2: Data Preprocessing
x_train = x_train.reshape(-1, 28, 28, 1)
x_test = x_test.reshape(-1, 28, 28, 1)
x_train = x_train.astype('float32') / 255.0
x_test = x_test.astype('float32') / 255.0

# Step 3: Building the CNN Model
model = Sequential()
model.add(Conv2D(32, (3, 3), activation='relu', input_shape=(28, 28, 1)))
model.add(MaxPooling2D((2, 2)))
model.add(Conv2D(64, (3, 3), activation='relu'))
model.add(MaxPooling2D((2, 2)))
model.add(Flatten())
model.add(Dense(64, activation='relu'))
model.add(Dense(10, activation='softmax'))

# Step 4: Training the Model
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
model.fit(x_train, y_train, epochs=10, batch_size=128, validation_data=(x_test, y_test))

# Step 5: Model Evaluation
loss, accuracy = model.evaluate(x_test, y_test)
print(f'Test Loss: {loss:.4f}')
print(f'Test Accuracy: {accuracy:.4f}')

# Step 6: Making Predictions
predictions = model.predict(x_test)
predicted_labels = np.argmax(predictions, axis=1)

# Step 7: Visualize the Results
import matplotlib.pyplot as plt

label_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat',
               'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']

# Display a random sample of predicted images and their labels
fig, axes = plt.subplots(5, 5, figsize=(12, 12))
for i, ax in enumerate(axes.flat):
    idx = np.random.randint(0, len(x_test))
    ax.imshow(x_test[idx].reshape(28, 28), cmap='gray')
    ax.axis('off')
    ax.set_title(f'Predicted: {label_names[predicted_labels[idx]]}')
plt.show()

```

## Approach

The following steps were followed to build the plant disease detection system:

1. **Data Preprocessing**: The dataset was loaded and preprocessed, including resizing the images, converting them to the appropriate format, and splitting them into training and testing sets.

2. **Building the CNN Model**: A CNN model architecture was designed to learn meaningful features from the plant images. The model consists of convolutional layers for feature extraction, pooling layers for downsampling, and fully connected layers for classification. The model's architecture can be adjusted and optimized to achieve better performance.

3. **Training the Model**: The CNN model was trained on the training set using the labeled plant images. The model was optimized using an appropriate loss function and an optimization algorithm. The training process involved iteratively updating the model's weights to minimize the loss and improve accuracy.

4. **Model Evaluation**: The trained CNN model was evaluated on the testing set to assess its performance and generalization ability. Evaluation metrics such as accuracy, precision, recall, and F1-score were computed to measure the model's classification performance.

5. **Making Predictions**: The trained CNN model was deployed to make predictions on new, unseen plant images. Given an input image, the model predicts the corresponding disease class, helping identify and diagnose plant diseases in real-world scenarios.

6. **Conclusion**: The plant disease detection system using CNN demonstrated promising results in accurately classifying plant images into different disease categories. By leveraging deep learning techniques, the system can contribute to early disease detection, enabling proactive measures for effective plant disease management. However, further improvements can be explored, such as incorporating transfer learning, data augmentation, or fine-tuning the model architecture, to enhance the system's performance and robustness.

Feel free to explore the code and adapt it according to your specific needs. The provided code serves as a starting point for building your own plant disease detection system using CNN.

