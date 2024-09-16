
# import numpy as np
# import matplotlib.pyplot as plt
# from sklearn.decomposition import PCA
# import os
# import importlib.util
# from sklearn.metrics.pairwise import cosine_similarity

# def import_script(script_path):
#     spec = importlib.util.spec_from_file_location("module.name", script_path)
#     module = importlib.util.module_from_spec(spec)
#     spec.loader.exec_module(module)
#     return module

# def extract_lists_from_module(module):
#     lists = {}
#     for name in dir(module):
#         obj = getattr(module, name)
#         if isinstance(obj, list):
#             lists[name] = obj
#     return lists

# folder_path = './output'

# words_and_embeddings = []

# # Load embeddings and corresponding words from all Python files in the folder
# for filename in os.listdir(folder_path):
#     if filename.endswith('.py'):
#         script_path = os.path.join(folder_path, filename)
#         module = import_script(script_path)
#         lists = extract_lists_from_module(module)
#         print(f'Lists in {filename}:')
#         for name, lst in lists.items():
#             if name == "weightVector":
#                 # Assuming 'word' is also stored in the script
#                 word = getattr(module, 'word', None)
#                 if word:
#                     embedding_array = np.array(lst)
#                     if embedding_array.size > 0:  # Check if the array is not empty
#                         words_and_embeddings.append((word, embedding_array))
#                     else:
#                         print(f"Warning: Empty embedding array found in {filename} for word '{word}'")

# if not words_and_embeddings:
#     print("No valid embeddings found.")
# else:
#     # Separate words and embeddings
#     words, embeddings = zip(*words_and_embeddings)

#     # Ensure that all embeddings have the same number of dimensions
#     embedding_lengths = [embedding.shape[0] for embedding in embeddings]
#     if len(set(embedding_lengths)) != 1:
#         print("Error: Not all embeddings have the same number of dimensions.")
#         print("Embedding lengths:", embedding_lengths)
#     else:
#         # Combine all embeddings into a single array
#         combined_embeddings = np.vstack(embeddings)

#         cosine_sim_matrix = cosine_similarity(combined_embeddings)

#         # Print the cosine similarity matrix with word labels
#         print("Cosine Similarity Matrix:")
#         print("\t" + "\t".join(words))
#         for i, word in enumerate(words):
#             print(word + "\t" + "\t".join(f"{cosine_sim_matrix[i][j]:.2f}" for j in range(len(words))))

#         # Reduce dimensions to 3D using PCA
#         pca = PCA(n_components=3)
#         reduced_embeddings = pca.fit_transform(combined_embeddings)

#         # Plotting
#         fig = plt.figure()
#         ax = fig.add_subplot(111, projection='3d')

#         # Scatter plot with labels
#         for i, word in enumerate(words):
#             ax.scatter(reduced_embeddings[i, 0], reduced_embeddings[i, 1], reduced_embeddings[i, 2])
#             ax.text(reduced_embeddings[i, 0], reduced_embeddings[i, 1], reduced_embeddings[i, 2], word)

#         ax.set_xlabel('X')
#         ax.set_ylabel('Y')
#         ax.set_zlabel('Z')
#         plt.show()

import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
import os
from sklearn.metrics.pairwise import cosine_similarity

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
        # Combine all embeddings into a single array
        combined_embeddings = np.vstack(embeddings)

        cosine_sim_matrix = cosine_similarity(combined_embeddings)

        # Print the cosine similarity matrix with word labels
        print("Cosine Similarity Matrix:")
        print("\t" + "\t".join(words))
        for i, word in enumerate(words):
            print(word + "\t" + "\t".join(f"{cosine_sim_matrix[i][j]:.2f}" for j in range(len(words))))

        # Reduce dimensions to 3D using PCA
        pca = PCA(n_components=3)
        reduced_embeddings = pca.fit_transform(combined_embeddings)

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
