import os
import pandas as pd
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

MEASUREMENTS_DIR = "../data/measurements/"
PLOTS_DIR = "../data/plots/"

ARCHIVOS = {
    "Naive": "naive.csv",
    "Strassen": "strassen.csv"
}

COLUMNAS = [
    "n",
    "tipo",
    "dominio",
    "muestra",
    "tiempo_us",
    "memoria_kb"
]

def leer_mediciones(nombre_archivo):
    ruta = os.path.join(MEASUREMENTS_DIR, nombre_archivo)
    df = pd.read_csv(
        ruta,
        header=None,
        names=COLUMNAS
    )

    df["n"] = pd.to_numeric(df["n"])
    df["tiempo_us"] = pd.to_numeric(df["tiempo_us"])
    df["memoria_kb"] = pd.to_numeric(df["memoria_kb"])

    return df

def cargar_datos():
    datos = []

    for algoritmo, archivo in ARCHIVOS.items():
        df = leer_mediciones(archivo)
        df["algoritmo"] = algoritmo
        datos.append(df)

    return pd.concat(datos, ignore_index=True)


def graficar_tiempo(datos):

    tipos = sorted(datos["tipo"].unique())
    dominios = sorted(datos["dominio"].unique())

    for tipo in tipos:
        for dominio in dominios:

            filtro = datos[
                (datos["tipo"] == tipo) &
                (datos["dominio"] == dominio)
            ]

            resumen = (
                filtro
                .groupby(
                    ["algoritmo", "n"],
                    as_index=False
                )["tiempo_us"]
                .mean()
            )

            plt.figure(figsize=(9, 6))

            for algoritmo in ARCHIVOS:

                parte = resumen[
                    resumen["algoritmo"] == algoritmo
                ]

                if parte.empty:
                    continue

                plt.plot(
                    parte["n"],
                    parte["tiempo_us"],
                    marker="o",
                    label=algoritmo
                )

            plt.xscale("log")
            plt.yscale("log")

            plt.xlabel("Tamaño de la matriz (n)")
            plt.ylabel("Tiempo promedio (microsegundos)")

            plt.title(
                f"Tiempo de ejecución - {tipo} - {dominio}"
            )

            plt.grid(True, which="both", alpha=0.3)
            plt.legend()
            plt.tight_layout()

            nombre = f"tiempo_{tipo}_{dominio}.png"

            plt.savefig(
                os.path.join(PLOTS_DIR, nombre)
            )

            plt.close()


def graficar_memoria(datos):

    tipos = sorted(datos["tipo"].unique())
    dominios = sorted(datos["dominio"].unique())
    for tipo in tipos:
        for dominio in dominios:

            filtro = datos[
                (datos["tipo"] == tipo) &
                (datos["dominio"] == dominio)
            ]

            resumen = (
                filtro
                .groupby(
                    ["algoritmo", "n"],
                    as_index=False
                )["memoria_kb"]
                .mean()
            )

            plt.figure(figsize=(9, 6))

            for algoritmo in ARCHIVOS:

                parte = resumen[
                    resumen["algoritmo"] == algoritmo
                ]

                if parte.empty:
                    continue

                plt.plot(
                    parte["n"],
                    parte["memoria_kb"],
                    marker="o",
                    label=algoritmo
                )

            plt.xscale("log")

            plt.xlabel("Tamaño de la matriz (n)")
            plt.ylabel("Memoria promedio (KB)")

            plt.title(
                f"Uso de memoria - {tipo} - {dominio}"
            )

            plt.grid(True, which="both", alpha=0.3)
            plt.legend()
            plt.tight_layout()

            nombre = f"memoria_{tipo}_{dominio}.png"

            plt.savefig(
                os.path.join(PLOTS_DIR, nombre)
            )
            plt.close()


def main():
    os.makedirs(PLOTS_DIR, exist_ok=True)
    datos = cargar_datos()
    graficar_tiempo(datos)
    graficar_memoria(datos)
    print("Gráficos generados correctamente.")

if __name__ == "__main__":
    main()
