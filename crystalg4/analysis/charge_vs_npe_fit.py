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

def spe_template(t, rise=2.2, decay=9, V_pe=2e-3):
    pulse = np.zeros_like(t)
    mask = t > 0
    shape = np.exp(-t[mask]/decay) - np.exp(-t[mask]/rise)
    if len(shape) > 0:
        shape /= np.max(shape)
    pulse[mask] = V_pe * shape
    return pulse

plt.figure(figsize=(10,6))

for fname, label in files:

    df = ROOT.RDataFrame("PMT", fname)
    data = df.AsNumpy()

    events = data["event"]
    times = data["time"]

    unique_events = np.unique(events)

    npe_list = []
    charge_list = []

    t = np.linspace(0, 200, 1000)

    for ev in unique_events:
        mask = (events == ev)
        phot_times = times[mask]

        if len(phot_times) == 0:
            continue

        Npe = len(phot_times)

        t0 = np.min(phot_times)
        phot_times = phot_times - t0

        waveform = np.zeros_like(t)

        for ti in phot_times:
            waveform += spe_template(t - ti)

        Q = np.trapezoid(waveform, t)

        npe_list.append(Npe)
        charge_list.append(Q)

    npe = np.array(npe_list)
    Q = np.array(charge_list)

    #ajuste lineal
    coeffs = np.polyfit(npe, Q, 1)
    slope, intercept = coeffs

    x_fit = np.linspace(min(npe), max(npe), 100)
    y_fit = slope * x_fit + intercept

    plt.scatter(npe, Q, s=10, alpha=0.4)
    plt.plot(x_fit, y_fit, label=f"{label} (G={slope:.3e})")

plt.xlabel("Npe")
plt.ylabel("Charge (mV*ns)")
plt.title("Charge vs Npe with Linear Fit")
plt.legend()
plt.grid()
plt.show()