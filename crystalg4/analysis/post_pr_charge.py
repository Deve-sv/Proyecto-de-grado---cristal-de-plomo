import numpy as np
import matplotlib.pyplot as plt
import ROOT

ROOT.ROOT.EnableImplicitMT()

files = [
    ("PMT_0.root", "0.1 GeV, 0"),
    ("PMT_1.root", "0.1 GeV, 30"),
    ("PMT_2.root", "0.2 GeV, 0"),
    ("PMT_3.root", "0.2 GeV, 30"),
    ("PMT_4.root", "0.3 GeV, 0"),
    ("PMT_5.root", "0.3 GeV, 30"),
]

#Modelo SPE 

def spe_template(t, rise=2.2, decay=9, V_pe=2e-3):
    pulse = np.zeros_like(t)
    mask = t > 0

    shape = np.exp(-t[mask]/decay) - np.exp(-t[mask]/rise)

    #normalizar forma a pico = 1
    if len(shape) > 0:
        shape /= np.max(shape)

    pulse[mask] = V_pe * shape

    return pulse

#t = np.linspace(0, 1000, 1000)

# =========================
# Dist. de carga
# =========================
plt.figure(figsize=(10,6))

for fname, label in files:

    df = ROOT.RDataFrame("PMT", fname)
    data = df.AsNumpy()

    events = data["event"]
    times = data["time"]

    unique_events = np.unique(events)

    charges = []

    #ventana fija coherente (tras centrar)
    t = np.linspace(0, 200, 1000)

    for ev in unique_events:
        mask = (events == ev)
        phot_times = times[mask]

        #centrar evento
        t0 = np.min(phot_times)
        phot_times = phot_times - t0

        waveform = np.zeros_like(t)

        for ti in phot_times:
            waveform += spe_template(t - ti)

        #calculo de carga correcto
        Q = np.trapezoid(waveform, t)
        charges.append(Q)

    plt.hist(charges, bins=50, alpha=0.5, label=label)

plt.xlabel("Charge (mV.ns)")
plt.ylabel("Counts")
plt.title("Charge Distribution")
plt.legend()
plt.grid()
plt.show()