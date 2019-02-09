const canvas = document.getElementById('snowflakes-canvas').getContext('2d');

async function instantiateWebAssembly(path, importObject) {
  const bytes = await window.fetch(path).then(x => x.arrayBuffer());
  return WebAssembly.instantiate(bytes, importObject);
}

function jsStringFromWasmMemory(memory, offset, size) {
  // We pass strings and other objects from WASM to JS by reading
  // the bytes starting at a memory location. WASM provides the
  // offset for where we need to start reading memory at.
  const bytes = new Uint8Array(memory.buffer, offset, size);
  return new TextDecoder('utf8').decode(bytes);
}

const memory = new WebAssembly.Memory({
  initial: 256, // 256 64KB pages of virtual memory
  maximum: 256
});

const table = new WebAssembly.Table({
  initial: 0,
  maximum: 0,
  element: 'anyfunc'
});

const importObject = {
  env: {
    'abortStackOverflow': _ => {
      throw new Error('stack overflow');
    },
    'table': table,
    'memory': memory,
    '__table_base': 0,
    '__memory_base': 0,
    'STACKTOP': 0,
    'STACK_MAX': memory.buffer.byteLength,
    _fill_canvas(colour, x, y, w, h) {
      canvas.fillStyle = jsStringFromWasmMemory(memory, colour, 7);
      canvas.fillRect(x, y, w, h);
    },
    _rand_num(max) {
      return Math.random() * max;
    }
  }
};

instantiateWebAssembly('snowflakes.wasm', importObject).then(wa => {
  const exports = wa.instance.exports;
  exports._init_snowflakes();

  function render() {
    exports._render_snowflakes();
    window.requestAnimationFrame(render);
  }

  render();
}).catch(err => console.warn('err loading wasm', err));
