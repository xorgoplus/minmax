import subprocess
import os
import matplotlib.pyplot as plt

EXECUTABLE_PATH = os.path.join(".", "graph", "minmax.exe")

SIZES = list(range(100_000_000, 500_000_001, 10_000_000))

def run_benchmark(kind: str, size: int) -> float:
    cmd = [EXECUTABLE_PATH, "--kind", kind, "--size", str(size)]
    try:
        result = subprocess.run(cmd, capture_output=True, text=True, check=True)
        time_taken = float(result.stdout.strip())
        return time_taken
    except Exception as e :
        return 0.0

def main():
    cpu_times = []
    simd_times = []

    for size in SIZES:

        t_cpu = run_benchmark("cpu", size)
        t_simd = run_benchmark("simd", size)


        cpu_times.append(t_cpu)
        simd_times.append(t_simd)

    plt.figure(figsize=(10, 6))

    plt.plot(SIZES, cpu_times, marker='o', linewidth=3, label='CPU', color='crimson')
    plt.plot(SIZES, simd_times, marker='s', linewidth=3, label='SIMD', color='teal')

    plt.title('CPU vs SIMD', fontsize=14)
    plt.xlabel('(N)', fontsize=12)
    plt.ylabel('(Sec)', fontsize=12)

    plt.grid(True, which="both", linestyle='--', alpha=0.5)
    plt.legend(fontsize=12)

    plt.xscale('log')
    plt.tight_layout()
    plt.savefig('performance_comparison.png', dpi=300)
    plt.show()

if __name__ == "__main__":
    main()