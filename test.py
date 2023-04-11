import os

TRACE_PATHS = ["compute_int_0", "srv_0", "compute_fp_1"]
W_LIST = [1, 2, 3, 4]
START_INSTRUCTIONS = [0, 1000000, 10000000, 15000000, 20000000, 25000000]
INST_COUNT = 1000000

if not os.path.exists("results"):
    os.mkdir("results")

for TRACE_PATH in TRACE_PATHS:
    for W in W_LIST:
        for START in START_INSTRUCTIONS:
            OUTPUT_FILE = f"results/{TRACE_PATH}_start{START}_w{W}.txt"
            os.system(
                f"./proj {TRACE_PATH} {START} {INST_COUNT} {W} > {OUTPUT_FILE}")
            print(
                f"Simulation for {TRACE_PATH} with {INST_COUNT} instructions starting at {START} and W={W} completed.")
