import os
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("data/measurements/mediciones_matrices.csv")

# Por tiempo [ms]
dfPromedio_t = df.groupby(["algoritmo","n"])["tiempo_ms"].mean().reset_index()
algoritmos = dfPromedio_t["algoritmo"].unique()
for alg in algoritmos:
    df_alg = dfPromedio_t[(dfPromedio_t["algoritmo"]==alg)]
    plt.plot(df_alg["n"],df_alg["tiempo_ms"],marker='o',label=alg)

plt.xlabel("n")
plt.ylabel("tiempo [ms]")
plt.legend()
plt.savefig("data/plots/matrix_multiplication_time.png")
plt.close()

# Por memoria [kb]
dfPromedio_m = df.groupby(["algoritmo","n"])["memoria_kb"].mean().reset_index()
algoritmos = dfPromedio_m["algoritmo"].unique()
for alg in algoritmos:
    df_alg = dfPromedio_m[(dfPromedio_m["algoritmo"]==alg)]
    plt.plot(df_alg["n"],df_alg["memoria_kb"],marker='o',label=alg)

plt.xlabel("n")
plt.ylabel("memoria [kb]")
plt.legend()
plt.savefig("data/plots/matrix_multiplication_memory.png")
plt.close()

os.makedirs("data/tablas", exist_ok=True)

tabla_promedios_tiempo = df.pivot_table(
    index='algoritmo',
    columns='n',
    values='tiempo_ms',
    aggfunc='mean'
)

tabla_promedios_memoria = df.pivot_table(
    index='algoritmo',
    columns='n',
    values='memoria_kb',
    aggfunc='mean'
)

tabla_promedios_tiempo.index.name = None
tabla_promedios_memoria.index.name = None

with open("data/tablas/time_matrix_multiplication.tex", "w") as f:
    contenido = tabla_promedios_tiempo.to_latex(
        caption="Tiempo promedio de ejecución (ms) por algoritmo y tamaño",
        label="tab:matrix_multiplication_tabla_tiempo",
        column_format="lrrrr",
        float_format="%.4f",
        decimal=","
    )
   
    contenido = contenido.replace(r"\begin{table}", r"\begin{table}[H]" + "\n" + r"\centering")
    f.write(contenido)

# Exportar Tabla de Memoria
with open("data/tablas/memory_matrix_multiplication.tex", "w") as f:
    contenido = tabla_promedios_memoria.to_latex(
        caption="Uso de memoria promedio (kb) por algoritmo y tamaño",
        label="tab:matrix_multiplication_tabla_memoria",  
        column_format="lrrrr",
        float_format="%.4f",
        decimal=","
    )
    contenido = contenido.replace(r"\begin{table}", r"\begin{table}[H]" + "\n" + r"\centering")
    f.write(contenido)
