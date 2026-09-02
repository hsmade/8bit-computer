#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if ! command -v kicad-cli >/dev/null 2>&1; then
  echo "error: kicad-cli not found in PATH" >&2
  exit 1
fi

shopt -s nullglob

boards=()
for dir in "$root_dir"/*/; do
  pcb_files=("$dir"/*.kicad_pcb)
  if (( ${#pcb_files[@]} == 1 )); then
    boards+=("${pcb_files[0]}")
  elif (( ${#pcb_files[@]} > 1 )); then
    echo "warning: skipping $dir because it has multiple .kicad_pcb files" >&2
  fi
done

if (( ${#boards[@]} == 0 )); then
  echo "error: no board directories with .kicad_pcb files found under $root_dir" >&2
  exit 1
fi

for pcb in "${boards[@]}"; do
  board_dir="$(dirname "$pcb")"
  board_name="$(basename "$pcb" .kicad_pcb)"
  sch="$board_dir/$board_name.kicad_sch"
  out_dir="$board_dir/renders"

  echo "==> $board_name"
  mkdir -p "$out_dir"

  kicad-cli pcb export svg \
    --mode-single \
    --page-size-mode 2 \
    --exclude-drawing-sheet \
    --layers F.Cu,F.Mask,F.Silkscreen,Edge.Cuts \
    --output "$out_dir/$board_name-pcb.svg" \
    "$pcb"

  if [[ -f "$sch" ]]; then
    kicad-cli sch export svg \
      --no-background-color \
      --output "$out_dir" \
      "$sch"
  else
    echo "warning: no matching schematic found for $pcb" >&2
  fi
done
