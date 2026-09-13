BUILD_DIR = build
GRAPH_DIR = graph
VENV_DIR = .venv

ifeq ($(OS),Windows_NT)
    PYTHON = $(VENV_DIR)\Scripts\python.exe
    PIP = $(VENV_DIR)\Scripts\pip.exe
    TARGET_BIN = minmax.exe
    RM_DIR = rmdir /s /q
    MKDIR = if not exist $(GRAPH_DIR) mkdir $(GRAPH_DIR)
else
    PYTHON = $(VENV_DIR)/bin/python
    PIP = $(VENV_DIR)/bin/pip
    TARGET_BIN = minmax
    RM_DIR = rm -rf
    MKDIR = mkdir -p $(GRAPH_DIR)
endif

.PHONY: all setup-venv build-c install-app graph clean

all: install-app graph

setup-venv:
	python -m venv $(VENV_DIR)
	$(PIP) install --upgrade pip
	$(PIP) install matplotlib

build-c:
	cmake -B $(BUILD_DIR) -S . -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles"
	cmake --build $(BUILD_DIR) --config Release

install-app: build-c
	cmake -E copy $(BUILD_DIR)/$(TARGET_BIN) $(GRAPH_DIR)/
graph: setup-venv install-app
	$(PYTHON) $(GRAPH_DIR)/main.py

clean:
	$(RM_DIR) $(BUILD_DIR)
	$(RM_DIR) $(VENV_DIR)
