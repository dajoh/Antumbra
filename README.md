Antumbra
========

A Minecraft style rendering experiment.

Lighting
--------

Lighting (both point light and skylight) unfortunately didn't make it into this version.
The algorithm for point light is as follows though:

```text
PointLight(x, y, z, level)
    SetLight(x, y, z, level)
    LightAxis(x, y, z, Right)
    LightAxis(x, y, z, Left)
    LightAxis(x, y, z, Up)
    LightAxis(x, y, z, Down)
    LightAxis(x, y, z, Forward)
    LightAxis(x, y, z, Backward)

LightAxis(x, y, z, direction)
    for(i = GetLight(x, y, z) - 1; i != 0; i--)
        switch(direction)
            Right    -> x++
            Left     -> x--
            Up       -> y++
            Down     -> y--
            Forward  -> z++
            Backward -> z--
        if(GetBlock(x, y, z) != Air)
            break
        else if(GetLight(x, y, z) >= i)
            break
        else
            SetLight(x, y, z, i)
        switch(direction)
            Right & Left ->
                LightAxis(x, y, z, Up)
                LightAxis(x, y, z, Down)
                LightAxis(x, y, z, Forward)
                LightAxis(x, y, z, Backward)
            Up & Down ->
                LightAxis(x, y, z, Right)
                LightAxis(x, y, z, Left)
                LightAxis(x, y, z, Forward)
                LightAxis(x, y, z, Backward)
            Forward & Backward ->
                LightAxis(x, y, z, Right)
                LightAxis(x, y, z, Left)
                LightAxis(x, y, z, Up)
                LightAxis(x, y, z, Down)
```

Skylight is the same, but has no vertical attenuation before it hits the ground.

Special Thanks
--------------

Special thanks to who Disco who created the Minecraft texture pack I got the textures from. You can check out his work here:
http://www.ocddisco.com/