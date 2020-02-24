import torch

def mul2(x):
  return x * 2
  
torch.jit.trace(mul2, torch.randn(3, 3)).save("mul2.pt")  