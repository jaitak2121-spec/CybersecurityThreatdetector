# Dockerfile - Cybersecurity Threat Detection & Incident Response Simulator
#
# Builds the real C++ OOP simulator and serves the existing presentation
# frontend (frontend/index.html + frontend/server.py). Designed to deploy
# on Render as a Docker web service.
#
# The image contains both Python 3 (to run the frontend/server) and g++
# (to build and, if ever needed, rebuild the C++ simulator).

FROM python:3.12-slim

# ---------------------------------------------------------------------------
# Install the C++ toolchain. build-essential provides g++, make and the
# standard build tools needed to compile the simulator.
# ---------------------------------------------------------------------------
RUN apt-get update \
    && apt-get install -y --no-install-recommends build-essential \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy the whole project into the image (.dockerignore trims what we skip).
COPY . /app

# ---------------------------------------------------------------------------
# Compile the C++ simulator at BUILD time. If the C++ does not compile the
# image build fails immediately (fast feedback), and the container then
# starts quickly because the binary is already present.
# ---------------------------------------------------------------------------
RUN g++ -std=c++17 -O2 -Wall -o simulator src/*.cpp

# Render supplies the port to listen on via $PORT. Default to 10000 so the
# image also works when run locally without that variable set.
ENV PORT=10000
EXPOSE 10000

# Start the Python frontend. It serves index.html and, on /api/run,
# executes the compiled ./simulator and returns its output.
CMD ["python3", "frontend/server.py"]
