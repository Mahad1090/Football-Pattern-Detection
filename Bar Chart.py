import matplotlib.pyplot as plt
import numpy as np

patterns = ['1', '12', '121', '123', '1212', '1213', '1231', '1232', '1234']

team_a_values = [66, 452, 1132, 237, 1132, 361, 228, 395, 66]
team_2_values = [65, 524, 950, 290, 950, 399, 363, 385, 65]

x = np.arange(len(patterns)) 
width = 0.4 

plt.figure(figsize=(10, 6))
plt.bar(x - width/2, team_a_values, width, label='Team A', color='blue')
plt.bar(x + width/2, team_2_values, width, label='Team 2', color='red')

plt.xlabel('Patterns', fontsize=12)
plt.ylabel('Values', fontsize=12)
plt.title('Bar Chart for Team A and Team 2', fontsize=14)
plt.xticks(x, patterns)
plt.legend()

plt.tight_layout()
plt.show()