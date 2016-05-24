# BICORDER

Copyright (c) 2016 - Gray Cat Labs - https://graycat.io

I put this project together for the OSH Park Bring A Hack meetup at the 2016 Bay Area Maker Faire. It's Tricorder inspired, but can't quite sense everything, so the name "Bicorder" seemed fitting. It currently has a 3-axis magnetometer, a relative humidity / temperature sensor and an infrared range finder. It uses a 128x32 pixel monochrome LCD from Newhaven, which is divided into left and right sections, each displaying one of:

 * live plot of temperature (in Celsius)
 * live plot of relative humidity
 * live plot of magnetic field (Z-axis) in uTesla
 * a compass display (using the mag X and Y)
 * a distance readout in cm

I kept it pretty well sectioned into separate libraries, some of which could certainly be reused in other projects. You can find all the source on [Github](https://github.com/graycatlabs/Bicorder).

## License

Released under the MIT license.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.