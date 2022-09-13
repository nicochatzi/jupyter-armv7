# Jupyter Notebooks for ARMv7 C++ code

## TL;DR

Check out [example/lab/example.html](example/lab/example.html) to see a Jupyter Notebook that
was generated using C++ code compiled for armv7 (raspberry pi 3)... but on my x86_64 machine!
Since the HTML is not hosted, just download and view it in a browser.

## Description

Python has become one of the languages for DSP, Data Science and AI.
It has a rich suite of packages for multi-dimensional arrays and fancy plotting with very little
boilerplate, c.f. [numpy](https://pypi.org/project/numpy/), [scipy](https://pypi.org/project/scipy/), [matplotlib](https://pypi.org/project/matplotlib/), [tensorflow](https://pypi.org/project/tensorflow/), [pandas](https://pypi.org/project/pandas/), [plotly](https://pypi.org/project/plotly/)... (a subset of which are used in this project)

This hack attempts to use part of this suite with code compiled for RaspberryPi3 (armv7).
This allows use of production-ready code, wrapped into a python module, in a context that is easy
to explore, test edge-cases and document through Jupyter Notebooks.

These notebooks can host dynamic plots and play rendered audio. Then they can be exported to
HTML. Once exported, they do not run python code. But they are not totally static. Plotly
graphs are rendered to HTML and the audio player is embedded into HTML. So we could imagine deploying
these HTML files and use them as a sort of [Storybook.js](https://storybook.js.org/) for audio code.

More than that, when we see what Spotify have done with [pedalboard](https://github.com/spotify/pedalboard), we could imagine this
setup being used for Data Augmentation or other AI-related experimentation such as audio-corpus generation (similar to [torchsynth](https://github.com/torchsynth)) or patch analysis/generation/modification based on categorisation.

To do this on an arbitrary machine, we need Docker containers running hardware emulation with QEMU.
Then we need to compile our engines and wrap them in Python modules, for this we use [pybind11](https://github.com/pybind/pybind11) with
the help of [scikit-build](https://pypi.org/project/scikit-build/). From there, we can start the Jupyter Notebook Server, connect to it,
and mess around.

## Requirements

Everything is contained in the Docker container with QEMU bundled in, so you should only need Docker v20.

## Running

To start working with this project you need to first build the ARM Linux container with

```
make docker-build
```

This may take a while depending on your network connection. It download a pre-configured container
then installs build tools (build-essential, Python, Jupyter, pybind11 + all packages listed in [requirements.txt](docker/env/requirements.txt)). The resulting container is large but contains everything on startup.
If you find it too large, you could try starting from a different base.

### Jupyter Server

To start the Jupyter Notebook Server, you need to instantiate and enter the container with

```
make docker-enter
```

Then from inside the image run

```
make start-jupyter
```

This will start the server at http://127.0.0.1:8888/?token=9ffede0825894254b2e042ea597d771089e11aed

You can follow the link or open one of the `.ipynb` files in this project and tell VSCode to use
the server at that URL. You should now be able to use the notebook as if it were native, except
that it is running on ARM Linux.

### Example

Once in the container, run

```
make example-build
```

This will build the cpp example code into a python module for ARM and install it in the Docker image's
system globally. You can try using `import example as m; print(m.add(1,2))` in the Python REPL,
test it with `make example-test` or through `example.ipynb` (make sure you start the Jupyter server, connect to it and then run that file).

## Next Steps

We could explore:
* Wrapping this all up into a nice CLI which would be relatively easy. We can imagine a tool which
takes as parameters things like target platform and python packages. It would then find the dockerfile
for the target platform and add the dependencies. From a developer's point of vue, nothing changes.
This would allow you to say "build for x86_64/aarch64/armv7", then we have an easy way to build, test
and document cross-architecture C++ based python packages without cross-compilers or VMs.
Similar to Rust's [cargo-cross](https://github.com/cross-rs/cross).
* Spotify's [pedalboard](https://github.com/spotify/pedalboard) doesn't compile for this hack's target platform, but it does for others!
This could be used to examine VST3/AU plugins. Taken a step further, this
could be be part of high-level audio plugin testbed, as an e2e test suite for signal processing.
* Running the Jupyter Server locally (outside of a container) and having it connect to Python kernel
on a target device, though performance has not really been an issue...
* Explore wrapping and running in the notebook with in other languages, e.g. Julia.

## Resources used for hack

* [pybind11](https://github.com/pybind/pybind11)
    * [docs](https://pybind11.readthedocs.io/en/stable/index.html)
    * [cmake_example](https://github.com/pybind/cmake_example)
* [Jupyter]()
    * ['Public' Server](https://jupyter-notebook.readthedocs.io/en/stable/public_server.html#automatic-password-setup)