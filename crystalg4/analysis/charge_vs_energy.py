import numpy as np
import matplotlib.pyplot as plt
import ROOT

ROOT.ROOT.EnableImplicitMT()

files = [
    ("PMT_0.root", 0.1),
    ("PMT_1.root", 0.1),
    ("PMT_2.root", 0.2),
    ("PMT_3.root", 0.2),
    ("PMT_4.root", 0.3),
    ("PMT_5.root", 0.3),
]

def spe_template(t, rise=2.2, decay=9, V_pe=2e-3):
    pulse = np.zeros_like(t)
    mask = t > 0
    shape = np.exp(-t[mask]/decay) - np.exp(-t[mask]/rise)
    if len(shape) > 0:
        shape /= np.max(shape)
    pulse[mask] = V_pe * shape
    return pulse

energy_dict = {}

t = np.linspace(0, 200, 1000)

for fname, energy in files:

    df = ROOT.RDataFrame("PMT", fname)
    data = df.AsNumpy()

    events = data["event"]
    times = data["time"]

    unique_events = np.unique(events)

    charges = []

    for ev in unique_events:
        mask = (events == ev)
        phot_times = times[mask]

        if len(phot_times) == 0:
            continue

        t0 = np.min(phot_times)
        phot_times = phot_times - t0

        waveform = np.zeros_like(t)

        for ti in phot_times:
            waveform += spe_template(t - ti)

        Q = np.trapezoid(waveform, t)
        charges.append(Q)

    if energy not in energy_dict:
        energy_dict[energy] = []

    energy_dict[energy].extend(charges)

# calcular promedios
energies = []
mean_Q = []
std_Q = []

for E in sorted(energy_dict.keys()):
    q = np.array(energy_dict[E])
    energies.append(E)
    mean_Q.append(np.mean(q))
    std_Q.append(np.std(q))

plt.errorbar(energies, mean_Q, yerr=std_Q, fmt='o')

plt.xlabel("Muon Energy (GeV)")
plt.ylabel("Mean Charge (mV*ns)")
plt.title("Mean Charge vs Energy")
plt.grid()
plt.show()