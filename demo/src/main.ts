import './style.css'
import typescriptLogo from './typescript.svg'
import viteLogo from '/vite.svg'
import { setupCounter } from './counter.ts'
import sus from 'pkg'
console.log(sus)

document.querySelector<HTMLDivElement>('#app')!.innerHTML = `
  <canvas width="1000" height="1000" class="canvas" id="canvas" oncontextmenu="event.preventDefault()"></canvas>
  <div>
    <a href="https://vitejs.dev" target="_blank">
      <img src="${viteLogo}" class="logo" alt="Vite logo" />
    </a>
    <a href="https://www.typescriptlang.org/" target="_blank">
      <img src="${typescriptLogo}" class="logo vanilla" alt="TypeScript logo" />
    </a>
    <h1>Vite + TypeScript</h1>
    <div class="card">
      <button id="counter" type="button"></button>
    </div>
    <p class="read-the-docs">
      Click on the Vite and TypeScript logos to learn more
    </p>
  </div>
`

setupCounter(document.querySelector<HTMLButtonElement>('#counter')!)

// console.log(sus.run())
// const canvas = document.getElementById('canvas')
// // sus.canvas = canvas
// sus.canvas = canvas
// sus.sus()
// // sus.