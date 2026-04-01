import numpy as np
import matplotlib.pyplot as plt
import ROOT

# =========================
# Flags de sim.
# =========================
USE_DARK_NOISE = True
USE_AFTERPULSES = True
USE_ELECTRONIC_NOISE = False

ROOT.ROOT.EnableImplicitMT()

# =========================
# Archivos y etiquetas
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
# Modelo de pulso
# =========================
def spe_template(t, rise=2.2, decay=9, V_pe=2e-3):
    pulse = np.zeros_like(t)
    mask = t > 0

    shape = np.exp(-t[mask]/decay) - np.exp(-t[mask]/rise)

    if len(shape) > 0:
        shape /= np.max(shape)

    pulse[mask] = V_pe * shape
    return pulse

# =========================
# Dark noise
# =========================
def add_dark_noise(times, rate=5e3, tmax=1000):
    rate_ns = rate * 1e-9
    mean = rate_ns * tmax

    n_dark = np.random.poisson(mean)
    dark_times = np.random.uniform(0, tmax, n_dark)

    return np.concatenate([times, dark_times])


# =========================
# Afterpulses
# =========================
def add_afterpulses(times, prob=0.05, tau=100):
    after_times = []

    for t in times:
        if np.random.rand() < prob:
            delay = np.random.exponential(tau)
            after_times.append(t + delay)

    return np.concatenate([times, after_times])
# Eje temporal
t = np.linspace(0, 500, 1000)

# =========================
# 1. UN SOLO PULSO (primer evento)
# =========================
plt.figure(figsize=(10,6))

for fname, label in files:

    df = ROOT.RDataFrame("PMT", fname)
    data = df.AsNumpy()

    events = data["event"]
    times = data["time"]

    ev0 = np.unique(events)[0]  # primer evento
    mask = (events == ev0)
    phot_times = times[mask]

    #centrar tiempos
    t0 = np.min(phot_times)
    phot_times = phot_times - t0

    t_max = np.max(phot_times)
    t = np.linspace(0, t_max + 50, 1000)


    # ===== incluir efectos del PMT =====

    times_evt = phot_times.copy()

    # 1. dark noise
    if USE_DARK_NOISE:
        times_evt = add_dark_noise(times_evt, rate=5e3, tmax=t[-1])

    # 2. afterpulses
    if USE_AFTERPULSES:
        times_evt = add_afterpulses(times_evt, prob=0.05, tau=100)

    # opcional: cortar fuera de ventana
    times_evt = times_evt[times_evt < t[-1]]

    # 3. construir senal
    waveform = np.zeros_like(t)
    for ti in times_evt:
        waveform += spe_template(t - ti)

    # 4. ruido elec 
    if USE_ELECTRONIC_NOISE:
        waveform += np.random.normal(0, 5e-4, len(t))

    plt.plot(t, waveform, label=label)

plt.title(f"Single Event Pulses (dark={USE_DARK_NOISE}, after={USE_AFTERPULSES}, noise={USE_ELECTRONIC_NOISE})")
plt.xlabel("Time")
plt.ylabel("Amplitude")
plt.legend()
plt.grid()
plt.show()


# =========================
# 2. VARIOS PULSOS (estructura)
# =========================
plt.figure(figsize=(10,6))

fname, label = files[0]  # solo un caso para ver estructura
df = ROOT.RDataFrame("PMT", fname)
data = df.AsNumpy()

events = data["event"]
times = data["time"]

unique_events = np.unique(events)

for ev in unique_events[:10]:  # primeros 10 eventos
    mask = (events == ev)
    phot_times = times[mask]

    # ===== incluir efectos del PMT =====

    times_evt = phot_times.copy()

    # 1. dark noise
    if USE_DARK_NOISE:
        times_evt = add_dark_noise(times_evt, rate=5e3, tmax=t[-1])

    # 2. afterpulses
    if USE_AFTERPULSES:
        times_evt = add_afterpulses(times_evt, prob=0.05, tau=100)

    # opcional: cortar fuera de ventana
    times_evt = times_evt[times_evt < t[-1]]

    # 3. construir senal
    waveform = np.zeros_like(t)
    for ti in times_evt:
        waveform += spe_template(t - ti)

    # 4. ruido elec 
    if USE_ELECTRONIC_NOISE:
        waveform += np.random.normal(0, 5e-4, len(t))

    plt.plot(t, waveform, alpha=0.5)

plt.title(f"Multiple Pulses ({label}) (dark={USE_DARK_NOISE}, after={USE_AFTERPULSES}, noise={USE_ELECTRONIC_NOISE})")
plt.xlabel("Time")
plt.ylabel("Amplitude")
plt.grid()
plt.show()


# =========================
# 3. PULSO PROMEDIO
# =========================
plt.figure(figsize=(10,6))

for fname, label in files:

    df = ROOT.RDataFrame("PMT", fname)
    data = df.AsNumpy()

    events = data["event"]
    times = data["time"]

    unique_events = np.unique(events)

    waveforms = []

    for ev in unique_events:
        mask = (events == ev)
        phot_times = times[mask]

        # ===== incluir efectos del PMT =====

        times_evt = phot_times.copy()

        # 1. dark noise
        if USE_DARK_NOISE:
           times_evt = add_dark_noise(times_evt, rate=5e3, tmax=t[-1])

        # 2. afterpulses
        if USE_AFTERPULSES:
            times_evt = add_afterpulses(times_evt, prob=0.05, tau=100)  

        # opcional: cortar fuera de ventana
        times_evt = times_evt[times_evt < t[-1]]

        # 3. construir senal
        waveform = np.zeros_like(t)
        for ti in times_evt:
            waveform += spe_template(t - ti)

        # 4. ruido elec 
        if USE_ELECTRONIC_NOISE:
            waveform += np.random.normal(0, 5e-4, len(t))

        waveforms.append(waveform)

    mean_waveform = np.mean(waveforms, axis=0)

    plt.plot(t, mean_waveform, label=label)

plt.title(f"Average Pulses (dark={USE_DARK_NOISE}, after={USE_AFTERPULSES}, noise={USE_ELECTRONIC_NOISE})")
plt.xlabel("Time")
plt.ylabel("Amplitude")
plt.legend()
plt.grid()
plt.show()



