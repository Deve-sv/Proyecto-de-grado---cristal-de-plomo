import numpy as np
import matplotlib.pyplot as plt
import ROOT

ROOT.ROOT.EnableImplicitMT()

# =========================
# Config. de archivos
# =========================
files = [
    ("PMT_0.root", "0.1 GeV, 0"),
    ("PMT_1.root", "0.1 GeV, 30"),
    ("PMT_2.root", "0.2 GeV, 0"),
    ("PMT_3.root", "0.2 GeV, 30"),
    ("PMT_4.root", "0.3 GeV, 0"),
    ("PMT_5.root", "0.3 GeV, 30"),
]

# =========================
# Modelo de pulso (PMT)
# =========================
def spe_template(t, rise=2.2, decay=9, amp=50e-3):
    pulse = np.zeros_like(t)
    
    mask = t > 0  # solo tiempos fisicos
    
    pulse[mask] = amp * (
        np.exp(-t[mask]/decay) - np.exp(-t[mask]/rise)
    )
    
    return pulse
# Eje temporal
#t = np.linspace(0, 1000, 1000)


# =========================
# 1. Pulsos promedio
# =========================
plt.figure(figsize=(10,6))

for fname, label in files:

    df = ROOT.RDataFrame("PMT", fname)
    data = df.AsNumpy()

    events = data["event"]
    times = data["time"]

    unique_events = np.unique(events)

    waveforms = []

    #ventana fija (desp. de centrar)
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

        waveforms.append(waveform)

    mean_waveform = np.mean(waveforms, axis=0)

    plt.plot(t, mean_waveform, label=label)

plt.xlabel("Time")
plt.ylabel("Amplitude")
plt.title("Average PMT Pulses")
plt.legend()
plt.grid()
plt.show()


# =========================
# 2. Dist. de amplitudes
# =========================
plt.figure(figsize=(10,6))

for fname, label in files:

    df = ROOT.RDataFrame("PMT", fname)
    data = df.AsNumpy()

    events = data["event"]
    times = data["time"]

    unique_events = np.unique(events)

    max_amplitudes = []

    #misma ventana fija
    t = np.linspace(0, 200, 1000)

    for ev in unique_events:
        mask = (events == ev)
        phot_times = times[mask]

        #centrar
        t0 = np.min(phot_times)
        phot_times = phot_times - t0

        waveform = np.zeros_like(t)

        for ti in phot_times:
            waveform += spe_template(t - ti)

        max_amplitudes.append(np.max(waveform))

    plt.hist(max_amplitudes, bins=50, alpha=0.5, label=label)

plt.xlabel("Peak amplitude")
plt.ylabel("Counts")
plt.title("Amplitude Distribution")
plt.legend()
plt.grid()
plt.show()