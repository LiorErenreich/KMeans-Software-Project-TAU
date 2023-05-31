# KMeans-Software-Project-TAU-Part-1

Welcome to the KMeans-Software-Project-TAU-Part-1! This project was developed as part of the Software Project course (0368-2161) at Tel Aviv University by [Moria Nachmany](https://github.com/MoriaNachmany) and [Lior Erenreich](https://github.com/LiorErenreich). The aim of this project is to implement the K-means clustering algorithm using both C and Python programming languages.

## Project Structure

The project repository consists of the following files:

1. [**kmeans - Software Project.pdf**](./kmeans%20-%20Software%20Project.pdf): This document contains the assignment instructions provided by the course instructor. It outlines the requirements and goals of the project.

2. [**kmeans.c**](./kmeans.c): This file contains the implementation of the K-means algorithm in the C programming language. The C implementation is intended to provide a high-performance version of the algorithm.

3. [**kmeans.py**](./kmeans.py): This file contains the implementation of the K-means algorithm in Python. The Python implementation focuses on readability and ease of use, providing a more user-friendly version of the algorithm.

## Prerequisites

To run the project, you need to have the following prerequisites installed on your system:

- For the C implementation:
  - A C compiler (e.g., GCC)
  
- For the Python implementation:
  - Python 3.x
  - NumPy library (can be installed using `pip install numpy`)

## Usage

To use this project, follow the steps below:

1. Clone the project repository to your local machine or download the source code files.

2. **C Implementation**:
   - Compile the `kmeans.c` file using a C compiler. For example, using GCC, you can run the following command in the terminal:
     ```
     gcc -ansi -Wall -Wextra -Werror -pedantic-errors kmeans.c -lm -o kmeans
     ```
   - Execute the compiled binary:
     ```
     ./kmeans 3 100 < input.txt
     ```
     In the above command, 3 represents the value of K (the number of clusters), and 100 represents the maximum number of iterations. The input data is read from the file input.txt.

3. **Python Implementation**:
   - Open a terminal or command prompt and navigate to the project directory.
   - Run the Python script using the following command:
     ```
     python kmeans.py 3 100 < input.txt
     ```
Make sure you have the necessary prerequisites installed and that the input file input.txt exists in the same directory as the script (kmeans.py) before executing these commands.

## Working of the K-means Algorithm

The K-means algorithm is a popular unsupervised machine learning algorithm used for clustering analysis. It aims to partition a given dataset into K clusters, where each data point belongs to the cluster with the nearest mean (centroid).

The algorithm works as follows:

1. **Initialization**: Choose K initial centroids randomly or based on some heuristic. These centroids represent the initial cluster centers.

2. **Assignment**: Assign each data point to the nearest centroid based on a distance metric, typically Euclidean distance. This step creates K clusters.

3. **Update**: Recalculate the centroids of each cluster by taking the mean of all the data points assigned to that cluster.

4. **Repeat**: Repeat steps 2 and 3 until convergence or until a maximum number of iterations is reached. Convergence occurs when the centroids no longer change significantly or when the maximum number of iterations is reached.

5. **Output**: The algorithm outputs the final K clusters along with their centroids.



<div align="center">
    <img src="https://upload.wikimedia.org/wikipedia/commons/e/ea/K-means_convergence.gif" alt="K-means convergence">
</div>



This animation illustrates the k-means clustering process. It shows the convergence of the algorithm at each iteration. During each iteration, the means (centers) of the clusters are updated, and the black lines are drawn based on the updated means. However, the data points are still labeled according to the closest mean from the previous iteration.



## Project Flow

The project follows a common structure for implementing the K-means algorithm. The algorithm works as follows:

1. **Initialization**: Initially, K centroids are randomly selected from the input data points. These centroids represent the initial cluster centers.

2. **Assignment**: Each data point is assigned to the nearest centroid based on the Euclidean distance between the point and the centroids. This step creates K clusters.

3. **Update**: The centroids are recalculated by taking the mean of all the data points assigned to each cluster. This step moves the centroids to the center of their respective clusters.

4. **Iteration**: Steps 2 and 3 are repeated until a stopping criterion is met. This criterion can be a maximum number of iterations or a convergence threshold indicating that the centroids have stabilized.

The project provides two implementations of the K-means algorithm to showcase different programming paradigms and language choices. The C implementation offers better performance and can handle large datasets efficiently, while the Python implementation focuses on readability and ease of understanding.

For further description and examples of how to run the project, follow the instructions provided in the assignment document. It includes guidelines on compiling and executing the C code, as well as running the Python script. Ensure that you have the necessary dependencies installed for the Python implementation.


Happy clustering!


