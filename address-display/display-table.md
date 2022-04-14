# Display table
Describes the segments to be lit per character

## Segments
```
  A
F   B
  G
E   C
  D   dp
```

| segment | pin |
|---------|-----|
| A       | 10  |
| B       | 9   |
| C       | 8   |
| D       | 5   |
| E       | 1   |
| F       | 2   |
| G       | 3   |
| dp      | 7   |

## Table

| Character | A   | B   | C   | D   | E   | F   | G   | dp  | byte |
|-----------|-----|-----|-----|-----|-----|-----|-----|-----|------|
| 0         | 1   | 1   | 1   | 1   | 1   | 1   | 0   | 0   | FC   |
| 1         | 0   | 1   | 1   | 0   | 0   | 0   | 0   | 0   | 60   |
| 2         | 1   | 1   | 0   | 1   | 1   | 0   | 1   | 0   | DA   |
| 3         | 1   | 1   | 1   | 1   | 0   | 0   | 1   | 0   | F2   |
| 4         | 0   | 1   | 1   | 0   | 0   | 1   | 1   | 0   | 66   |
| 5         | 1   | 0   | 1   | 1   | 0   | 1   | 1   | 0   | B6   |
| 6         | 1   | 0   | 1   | 1   | 1   | 1   | 1   | 0   | BE   |
| 7         | 1   | 1   | 1   | 0   | 0   | 0   | 0   | 0   | E0   |
| 8         | 1   | 1   | 1   | 1   | 1   | 1   | 1   | 0   | FE   |
| 9         | 1   | 1   | 1   | 1   | 0   | 1   | 1   | 0   | F6   |
| A         | 1   | 1   | 1   | 0   | 1   | 1   | 1   | 0   | EE   |
| B         | 0   | 0   | 1   | 1   | 1   | 1   | 1   | 0   | 3E   |
| C         | 1   | 0   | 0   | 1   | 1   | 1   | 0   | 0   | 9C   |
| D         | 0   | 1   | 1   | 1   | 1   | 0   | 1   | 0   | 7A   |
| E         | 1   | 0   | 0   | 1   | 1   | 1   | 1   | 0   | 9E   |
| F         | 1   | 0   | 0   | 0   | 1   | 1   | 1   | 0   | 8E   |


## Rom addressing

8 bits input, bit 9 for left/right display

| A0-A7 | A8  | Address | Data | Display |
|-------|-----|---------|------|---------|
| 0x00  | 0   | 0x000   | 0    | Right   |
| 0x00  | 1   | 0x100   | 0    | Left    |
| 0x01  | 0   | 0x001   | 1    | Right   |
| 0x01  | 1   | 0x101   | 0    | Left    |
| 0x0F  | 0   | 0x00F   | F    | Right   |
| 0x0F  | 1   | 0x10F   | 0    | Left    |
| 0x20  | 0   | 0x020   | 0    | Right   |
| 0x20  | 1   | 0x120   | 2    | Left    |