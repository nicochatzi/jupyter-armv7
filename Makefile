DOCKERFILE=docker/rpi3.dockerfile
IMAGE=hackday/dsp-testbench
JUPYTER_TOKEN='9ffede0825894254b2e042ea597d771089e11aed'

docker-build:
	docker build -f $(DOCKERFILE) -t $(IMAGE) .

docker-enter:
	docker run -it --privileged \
		-p 8888:8888 \
		--platform linux/arm/v7 \
		--memory='2g' --cpus=4.0 --cpuset-cpus='0-3' \
		-v $(shell pwd):/mnt/app -w /mnt/app \
		$(IMAGE) bash

start-jupyter:
	jupyter notebook \
		--port=8888 --no-browser --ip=0.0.0 --allow-root \
		--NotebookApp.allow_password_change=True \
		--NotebookApp.token=$(JUPYTER_TOKEN) \
		--NotebookApp.password=''

example-build:
	pip install ./example

example-test:
	cd example && pytest tests/test.py