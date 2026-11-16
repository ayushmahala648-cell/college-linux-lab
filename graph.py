import matplotlib.pyplot as plt

def calculate_seek_count(sequence):
    return sum(abs(sequence[i] - sequence[i - 1]) for i in range(1, len(sequence)))

# 1. First-Come, First-Served (FCFS)
def fcfs(requests, head):
    return [head] + list(requests)

# 2. Shortest Seek Time First (SSTF)
def sstf(requests, head):
    pending = list(requests)
    sequence = [head]
    curr = head
    while pending:
        closest = min(pending, key=lambda x: abs(x - curr))
        sequence.append(closest)
        pending.remove(closest)
        curr = closest
    return sequence

# 3. SCAN (Elevator)
def scan(requests, head, disk_size=200, direction="right"):
    left = sorted([r for r in requests if r < head], reverse=True)
    right = sorted([r for r in requests if r >= head])
    if direction == "right":
        return [head] + right + ([disk_size - 1] if left else []) + left
    else:
        return [head] + left + ([0] if right else []) + right

# 4. C-SCAN (Circular SCAN)
def c_scan(requests, head, disk_size=200, direction="right"):
    left = sorted([r for r in requests if r < head])
    right = sorted([r for r in requests if r >= head])
    if direction == "right":
        return [head] + right + ([disk_size - 1, 0] if left else []) + left
    else:
        return [head] + left[::-1] + ([0, disk_size - 1] if right else []) + right[::-1]

# 5. LOOK
def look(requests, head, direction="right"):
    left = sorted([r for r in requests if r < head], reverse=True)
    right = sorted([r for r in requests if r >= head])
    return [head] + (right + left if direction == "right" else left + right)

# 6. C-LOOK
def c_look(requests, head, direction="right"):
    left = sorted([r for r in requests if r < head])
    right = sorted([r for r in requests if r >= head])
    return [head] + (right + left if direction == "right" else left[::-1] + right[::-1])

def plot_disk_scheduling(algorithms_data, disk_size=200):
    fig, axes = plt.subplots(2, 3, figsize=(16, 9))
    axes = axes.flatten()

    for idx, (name, seq) in enumerate(algorithms_data.items()):
        ax = axes[idx]
        steps = list(range(len(seq)))
        total_seek = calculate_seek_count(seq)

        # Plot track numbers on X-axis and step progression downward on Y-axis
        ax.plot(seq, steps, marker='o', linestyle='-', color='#1f77b4', linewidth=2, markersize=6)
        
        # Annotate each point with its cylinder/track number
        for step, track in zip(steps, seq):
            ax.annotate(str(track), (track, step), textcoords="offset points", xytext=(0, -12), ha='center', fontsize=8)

        ax.set_title(f"{name}\nTotal Head Movement: {total_seek}", fontsize=11, fontweight='bold')
        ax.set_xlim(0, disk_size - 1)
        ax.invert_yaxis()  # Top-to-bottom time progression (standard OS textbook style)
        ax.xaxis.tick_top()
        ax.xaxis.set_label_position('top')
        ax.set_xlabel("Track / Cylinder Number", fontsize=9)
        ax.set_ylabel("Step", fontsize=9)
        ax.grid(True, linestyle='--', alpha=0.6)

    plt.tight_layout()
    plt.savefig("disk_scheduling_comparison.png", dpi=300)
    plt.show()

if __name__ == "__main__":
    # Sample input from standard OS examples
    request_queue = [98, 183, 37, 122, 14, 124, 65, 67]
    initial_head = 53
    total_cylinders = 200  # Tracks 0 to 199

    results = {
        "FCFS": fcfs(request_queue, initial_head),
        "SSTF": sstf(request_queue, initial_head),
        "SCAN (Right)": scan(request_queue, initial_head, total_cylinders, "right"),
        "C-SCAN (Right)": c_scan(request_queue, initial_head, total_cylinders, "right"),
        "LOOK (Right)": look(request_queue, initial_head, "right"),
        "C-LOOK (Right)": c_look(request_queue, initial_head, "right"),
    }

    for algo, path in results.items():
        print(f"{algo:15} | Seek Count: {calculate_seek_count(path):3} | Path: {path}")

    plot_disk_scheduling(results, total_cylinders)
