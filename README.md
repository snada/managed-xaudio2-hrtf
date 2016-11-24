# XAudio2 Hrtf Wrapper for .NET

This is a small library to quickly and prototype .NET apps with real hrtf positional audio with a super simple interface, without the need of a huge middleware like Unity.

It's a simple wrapper over the [XAudio 2 HRTF XAPO](https://developer.microsoft.com/it-it/windows/holographic/spatial_sound_in_directx), introduced by Microsoft to develop immersive apps with Hololens.

## Requirements

- This library targets Microsoft Windows 10 only, as it leverages the latest XAudio 2.9, shipped by default with this system version. **Previous Windows versions won't work.**

- XAudio 2 hrtf APO only supports **48k samplerate mono wav files**. There's no conversion on any kind in this library for now, so act accordingly.

## Usage

### Create a positional sound

```C#
PositionalSound sound = new PositionalSound("path_to/sound_file.wav");
```

Creates an infinite looping positional sound, placed in the origin, in a Small environment.

```C#
PositionalSound sound = new PositionalSound("path_to/sound_file.wav", 10);
```

Creates a positional sound lasting 10 loops, in a small environment.

```C#
PositionalSound sound = new PositionalSound("path_to/sound_file.wav", 10, HrtfEnvironment.Outdoors);
```

Creates a positional sound lasting 10 loops, in a Outdoor environment.

### Play a sound

```C#
sound.Play();
```

### Stop a sound

```C#
sound.Stop();
```

### Change position of a sound

```C#
sound.X = 1.0f;
sound.Y = 10;
sound.Z = -2.0f;
```

```C#
sound.SetPosition(1.0f, 10, -2.0f);
```

Both these methods will immediately update the sound, as soon as values change.

### Change volume

```C#
sound.Volume = 0.5f;
```

### Hrtf Environments

A sound will react differently to the size of the surrounding environment. You can change a sound environment at any moment via the HrtfEnvironment enum:

```C#
sound.Environment = HrtfEnvironment.Medium;
```

These environments are currently available:

- Small
- Medium
- Large
- Outdoors

## Try the project

This project ships with a simple WPF test app, allowing to play with the library features. Clone the repository, build the solution and run Xaudio2HrtfWPFTest project.

## Contribution

As you can see, this library is far from being complete: only omnidirectional sources with very basic customization.
If anyone finds this project interesting and wants to fill the gaps, improve testing or anything else, can freely do so.

## License

This code is released under MIT license.

The test sound and part of the WAV loader comes from [Microsoft Universal Samples](https://github.com/Microsoft/Windows-universal-samples/blob/master/Samples/SpatialSound/README.md) also released under MIT license.
