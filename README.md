# ⚡ Parallel Algorithms

Parallel computing assignments implementing high-performance algorithms using OpenMP, MPI, and CUDA/Numba.

## Overview

This repository contains solutions to parallel programming assignments exploring different parallelization paradigms:
- **Shared memory** parallelism (OpenMP)
- **Distributed memory** parallelism (MPI)
- **GPU** computing (CUDA via Numba)
- **Branch & bound** optimization

## Assignments

| # | Name | Paradigm | Problem |
|---|------|----------|---------|
| HW1 | Storage | [OpenMP](https://en.wikipedia.org/wiki/OpenMP) | Parallel MST (Prim) + Levenshtein distance |
| HW2 | Heat Diffusion | [MPI](https://en.wikipedia.org/wiki/Message_Passing_Interface) | 2D heat equation simulation |
| HW4 | Maze Policy | [CUDA/Numba](https://en.wikipedia.org/wiki/CUDA) | Policy iteration on GPU |
| Slack | Bratley Scheduler | Branch & Bound | Task scheduling with deadlines |

## Project Structure

```
├── hw1_omp_skeletons/         # OpenMP: Parallel graph algorithms
│   └── src/
│       ├── Storage.cpp        # Prim's MST + Edit distance
│       └── Utils.h
│
├── hw2_mpi_skeletons_cp/      # MPI: Distributed heat simulation
│   └── src/
│       ├── HeatDiffusion.cpp  # 2D diffusion with domain decomposition
│       └── instances/         # Test grids
│
├── hw4_numba_skeletons/       # CUDA: GPU maze solver
│   ├── main.py                # Policy iteration kernel
│   └── hw4_numba_public/      # Test mazes
│
└── slack_brat/                # Branch & Bound scheduler
    ├── main.cpp               # Bratley's algorithm
    └── public/                # Test instances
```

## Algorithms & Techniques

### HW1 — OpenMP Parallelization
- **Prim's MST** — Parallel minimum key finding
- **Levenshtein Distance** — Space-optimized DP with parallel row computation

### HW2 — MPI Domain Decomposition
- **2D Heat Equation** — $\frac{\partial T}{\partial t} = \alpha \nabla^2 T$
- **Row-wise partitioning** — Each rank handles horizontal strips
- **Halo exchange** — Ghost cell communication between neighbors

### HW4 — GPU Policy Iteration
- **BFS-based policy** — Compute optimal directions to goal
- **CUDA kernels** — Parallel value updates via Numba

### Slack — Branch & Bound Scheduling
- **Bratley's Algorithm** — Optimal task scheduling
- **Pruning** — Slack-based upper bound elimination

## Tech Stack

| Component | Technology |
|-----------|------------|
| Languages | C++, Python |
| Parallel | OpenMP, MPI, CUDA (Numba) |
| Build | CMake |
| Visualization | Matplotlib, Netpbm (PPM) |

## Building

```bash
# OpenMP (HW1)
cd hw1_omp_skeletons/cmake-openmp
cmake . && make

# MPI (HW2)
cd hw2_mpi_skeletons_cp/cmake
cmake . && make
mpirun -np 4 ./HeatDiffusion input.txt output.ppm

# Numba (HW4)
pip install numba numpy matplotlib
python hw4_numba_skeletons/main.py
```
