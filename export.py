import pandas as pd
from statsmodels.formula.api import ols
import xlsxwriter

TRACE_PATHS = ["compute_int_0", "srv_0", "compute_fp_1"]
W_LIST = [1, 2, 3, 4]
START_INSTRUCTIONS = [0, 1000000, 10000000, 15000000, 20000000, 25000000]
INST_COUNT = 1000000
stats = []
for TRACE_PATH in TRACE_PATHS:
    for W in W_LIST:
        for START in START_INSTRUCTIONS:
            output_file = f"results/{TRACE_PATH}_start{START}_w{W}.txt"
            with open(output_file, "r") as f:
                line = f.readline().strip()
                values = [float(x) for x in line.split(",")]
                print(values)
                if TRACE_PATH == "compute_int_0":
                    script = "comp_int"
                elif TRACE_PATH == "compute_fp_1":
                    script = "comp_fp"
                else:
                    script = "srv"
                stats.append((script, START, W, values[0], values[1], values[2],
                              values[3], values[4], values[5]))

df = pd.DataFrame(stats, columns=[
                  'Script', 'Start', 'W', 'ExecTime', 'Int', 'FP', 'Branch', 'Load', 'Store'])


df = df.sort_values(['Start', 'W'])

workbook = xlsxwriter.Workbook('results.xlsx')
worksheet = workbook.add_worksheet()

worksheet.write_row(0, 0, ['Script', 'Start Instruction', 'W',
                    'ExecTime', 'Int', 'FP', 'Branch', 'Load', 'Store'])

for i, row in df.iterrows():
    worksheet.write_row(i+1, 0, row)

workbook.close()
