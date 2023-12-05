import sys
import os

from PIL import Image

outnameLoc = sys.argv[1].index('.')
outname = sys.argv[1][:outnameLoc]

with Image.open(sys.argv[1]) as im:
     im.save(outname + ".png")
os.remove(sys.argv[1])