import numpy as np
import matplotlib.pyplot as plt
import ROOT

#Enable implicit multi-threading
ROOT.ROOT.EnableImplicitMT()

#df=ROOT.RDataFrame("1", "res_1.root")
df=ROOT.RDataFrame("PMT", "PMT_0.root")

phot_times=df.AsNumpy()["time"]

print(phot_times)

def spe_template(t, rise=2.2, decay=9, V_pe=2e-3):
    pulse = np.zeros_like(t)
    mask = t > 0

    shape = np.exp(-t[mask]/decay) - np.exp(-t[mask]/rise)

    if len(shape) > 0:
        shape /= np.max(shape)

    pulse[mask] = V_pe * shape
    return pulse

def add_dark_noise(times, rate=5e3, tmax=1000):
    rate_ns = rate * 1e-9
    mean = rate_ns * tmax

    n_dark = np.random.poisson(mean)
    dark_times = np.random.uniform(0, tmax, n_dark)

    return np.concatenate([times, dark_times])

def add_afterpulses(times, prob=0.05, tau=100):
    after_times = []

    for t in times:
        if np.random.rand() < prob:
            delay = np.random.exponential(tau)
            after_times.append(t + delay)

    return np.concatenate([times, after_times])

def triangle_pulse(t, t0, amplitude, rise_time, fall_time):
    """Generate a triangle pulse at time t0"""
    dt = t - t0
    total_width = rise_time + fall_time
    
    if dt < 0 or dt > total_width:
        return 0
    elif dt < rise_time:
        return amplitude * (dt / rise_time)
    else:
        return amplitude * (1 - (dt - rise_time) / fall_time)


t = np.linspace(0, 1000, 1000)

# 1. fotoelectrones reales (Geant4)
times = phot_times.copy()

# 2. + dark noise
times = add_dark_noise(times, rate=5e3, tmax=t[-1])

# 3. + afterpulses
times = add_afterpulses(times, prob=0.05, tau=100)

# 4. construir 
waveform = np.zeros_like(t)

for ti in times:
    waveform += spe_template(t - ti)

# 5. ruido elec. (opcional, small.)
waveform += np.random.normal(0, 5e-4, len(t))

plt.plot(waveform)
plt.show()



"""
# Generate waveform
time_array = np.arange(0, 100, 0.1)  # 100 ns range, 0.1 ns steps
waveform = np.zeros_like(time_array)

for photon_time in phot_times:
    pulse = [triangle_pulse(t, photon_time, 1.0, 2.0, 8.0) 
             for t in time_array]
    waveform += pulse

plt.plot(time_array, waveform)
plt.show()
"""

