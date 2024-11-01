import numpy as np
import matplotlib.pyplot as plt
import os
from sklearn.metrics.pairwise import cosine_similarity
import umap.umap_  # Correct import for UMAP

def parse_custom_csv(file_path):
    word = None
    hot_vector = None
    weight_vector = []

    with open(file_path, 'r') as file:
        for line in file:
            line = line.strip()
            if line.startswith("word%"):
                word = line.split('%')[1]
            elif line.startswith("hotVector%"):
                hot_vector = [int(v) for v in line.split('%')[1].split(',')]
            elif line.startswith("weightVector%"):
                # Reconstruct the weight vector with custom delimiters
                weight_string = line.split('%')[1]
                weight_rows = weight_string.split('&')
                for row in weight_rows:
                    weight_vector.extend([float(v) for v in row.split(',')])
    
    if word and weight_vector:
        return word, np.array(weight_vector)
    else:
        print(f"Error parsing {file_path}")
        return None, None

folder_path = './output'

words_and_embeddings = []

# Load embeddings and corresponding words from all CSV files in the folder
for filename in os.listdir(folder_path):
    if filename.endswith('.csv'):
        file_path = os.path.join(folder_path, filename)
        word, embedding_array = parse_custom_csv(file_path)
        if word and embedding_array.size > 0:
            words_and_embeddings.append((word, embedding_array))
        else:
            print(f"Warning: Empty or invalid embedding array found in {filename} for word '{word}'")

if not words_and_embeddings:
    print("No valid embeddings found.")
else:
    # Separate words and embeddings
    words, embeddings = zip(*words_and_embeddings)

    # Ensure that all embeddings have the same number of dimensions
    embedding_lengths = [embedding.shape[0] for embedding in embeddings]
    if len(set(embedding_lengths)) != 1:
        print("Error: Not all embeddings have the same number of dimensions.")
        print("Embedding lengths:", embedding_lengths)
    else:
        embeddings = list(embeddings)

        # Multiply each embedding by 10000
        for i in range(len(embeddings)):
            embeddings[i] = embeddings[i] * 10000

        # Convert back to tuple if needed later
        embeddings = tuple(embeddings)
        # Combine all embeddings into a single array
        combined_embeddings = np.vstack(embeddings)

        cosine_sim_matrix = cosine_similarity(combined_embeddings)

        # Print the cosine similarity matrix with word labels
        print("Cosine Similarity Matrix:")
        print("\t" + "\t".join(words))
        for i, word in enumerate(words):
            print(word + "\t" + "\t".join(f"{cosine_sim_matrix[i][j]:.2f}" for j in range(len(words))))

        # Reduce dimensions to 3D using UMAP
        umap_model = umap.umap_.UMAP(n_components=3, random_state=42)
        reduced_embeddings = umap_model.fit_transform(combined_embeddings)

        # Plotting
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')

        # Scatter plot with labels
        for i, word in enumerate(words):
            ax.scatter(reduced_embeddings[i, 0], reduced_embeddings[i, 1], reduced_embeddings[i, 2])
            ax.text(reduced_embeddings[i, 0], reduced_embeddings[i, 1], reduced_embeddings[i, 2], word)

        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.set_zlabel('Z')
        plt.show()
