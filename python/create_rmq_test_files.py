from random import *


def main():
  sizes = []
  stepsize = 10
  for _ in range(1, 5):
    for j in range(stepsize, 10 * stepsize, stepsize):
      sizes.append(j)
    stepsize = stepsize * 10

  for size in sizes:
    generateRmqTestFile(size)

def generateRmqTestFile(size):
  file = open(f"../testfiles/rmq/generated/generated_example_{size}.txt", "w")
  file.write(f"{size}\n")

  # generate array
  for _ in range(0, size):
    a = randint(0, 2 * size)
    file.write(f"{a}\n")

  # generate requests
  for _ in range(0, 3 * size):
    a = randint(0, size - 1)
    b = randint(a, size - 1)
    str = f"{a},{b}\n"
    file.write(str)

  file.close()


if __name__ == "__main__":
  main()