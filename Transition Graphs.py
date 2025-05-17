import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

patterns = ['1', '12', '121', '123', '1212', '1213', '1231', '1232', '1234']
team1_data = [66, 452, 1132, 237, 1132, 361, 228, 395, 66]
team2_data = [65, 524, 950, 290, 950, 399, 363, 385, 65]

def generate_synthetic_transitions(data):
    transition_counts = np.zeros((len(data), len(data)))

    for i in range(len(data)):
        weights = np.array(data)
        synthetic_transitions = np.random.multinomial(data[i], weights / weights.sum())
        transition_counts[i] = synthetic_transitions
    
    return transition_counts

def create_transition_matrix(transition_counts):
    transition_matrix = np.zeros_like(transition_counts, dtype=float)

    for i in range(transition_counts.shape[0]):
        row_sum = transition_counts[i].sum()
        if row_sum > 0:
            transition_matrix[i] = transition_counts[i] / row_sum
    
    return transition_matrix

team1_transitions = generate_synthetic_transitions(team1_data)
team2_transitions = generate_synthetic_transitions(team2_data)

team1_transition_matrix = create_transition_matrix(team1_transitions)
team2_transition_matrix = create_transition_matrix(team2_transitions)

def plot_transition_heatmap(transition_matrix, patterns, team_name):
    plt.figure(figsize=(8, 6))
    
    sns.heatmap(
        transition_matrix, annot=True, cmap='PiYG', fmt='.2f', 
        xticklabels=patterns, yticklabels=patterns, cbar_kws={'label': 'Transition Probability'}
    )
    plt.title(f"Transition Matrix for {team_name}", fontsize=16)
    plt.xlabel('To Pattern')
    plt.ylabel('From Pattern')
    plt.show()

plot_transition_heatmap(team1_transition_matrix, patterns, 'Team 1')
plot_transition_heatmap(team2_transition_matrix, patterns, 'Team 2')