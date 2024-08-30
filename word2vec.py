import gensim
from gensim.models import Word2Vec
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
from sklearn.metrics.pairwise import cosine_similarity
import numpy as np

# Function to read text file and preprocess
def read_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        text = file.read()
    # Simple preprocessing: lowercase and split by whitespace
    words = text.lower().split()
    return [words]

# Train Word2Vec model
def train_word2vec(sentences):
    model = Word2Vec(sentences, vector_size=3, window=5, min_count=1, workers=4)
    return model

# Plot word embeddings in 3D
def plot_embeddings_3d(model):
    words = list(model.wv.index_to_key)
    vectors = np.array([model.wv[word] for word in words])

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    
    ax.scatter(vectors[:, 0], vectors[:, 1], vectors[:, 2])

    for i, word in enumerate(words):
        ax.text(vectors[i, 0], vectors[i, 1], vectors[i, 2], word)

    plt.show()

# Print cosine similarity matrix
def print_cosine_similarity_matrix(model):
    words = list(model.wv.index_to_key)
    vectors = np.array([model.wv[word] for word in words])
    similarity_matrix = cosine_similarity(vectors)

    print("Cosine Similarity Matrix:")
    print(f"{'':>15}", end="")
    for word in words:
        print(f"{word:>15}", end="")
    print()
    for i, word in enumerate(words):
        print(f"{word:>15}", end="")
        for j in range(len(words)):
            print(f"{similarity_matrix[i, j]:15.4f}", end="")
        print()

# Main function
def main():
    file_path = 'data\\index.txt'  # Replace with the path to your text file
    sentences = read_file(file_path)
    model = train_word2vec(sentences)
    plot_embeddings_3d(model)
    print_cosine_similarity_matrix(model)

if __name__ == "__main__":
    main()
