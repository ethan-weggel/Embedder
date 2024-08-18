# import numpy as np
# import matplotlib.pyplot as plt
# from sklearn.decomposition import PCA
# import os
# import importlib.util

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

# embeddings = []

# # Load embeddings from all Python files in the folder
# for filename in os.listdir(folder_path):
#     if filename.endswith('.py'):
#         script_path = os.path.join(folder_path, filename)
#         module = import_script(script_path)
#         lists = extract_lists_from_module(module)
#         for name, lst in lists.items():
#             if name == "weightVector":
#                 embeddings.append(np.array(lst))

# # Combine all embeddings into a single array
# combined_embeddings = np.vstack(embeddings)

# # Reduce dimensions to 3D using PCA
# pca = PCA(n_components=3)
# reduced_embeddings = pca.fit_transform(combined_embeddings)

# # Plotting
# fig = plt.figure()
# ax = fig.add_subplot(111, projection='3d')
# ax.scatter(reduced_embeddings[:, 0], reduced_embeddings[:, 1], reduced_embeddings[:, 2])

# ax.set_xlabel('X')
# ax.set_ylabel('Y')
# ax.set_zlabel('Z')
# plt.show()

import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
import os
import importlib.util

def import_script(script_path):
    spec = importlib.util.spec_from_file_location("module.name", script_path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

def extract_lists_from_module(module):
    lists = {}
    for name in dir(module):
        obj = getattr(module, name)
        if isinstance(obj, list):
            lists[name] = obj
    return lists

folder_path = './pre-output'

words_and_embeddings = []

# Load embeddings and corresponding words from all Python files in the folder
for filename in os.listdir(folder_path):
    if filename.endswith('.py'):
        script_path = os.path.join(folder_path, filename)
        module = import_script(script_path)
        lists = extract_lists_from_module(module)
        print(f'Lists in {filename}:')
        for name, lst in lists.items():
            if name == "weightVector":
                # Assuming 'word' is also stored in the script
                word = getattr(module, 'word', None)
                if word:
                    words_and_embeddings.append((word, np.array(lst)))

# Separate words and embeddings
words, embeddings = zip(*words_and_embeddings)

# Combine all embeddings into a single array
combined_embeddings = np.vstack(embeddings)

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
