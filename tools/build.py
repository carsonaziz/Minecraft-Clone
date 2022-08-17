import subprocess

# Mac Build
subprocess.call("make config=debug", shell=True)
# subprocess.call("make config=release", shell=True)