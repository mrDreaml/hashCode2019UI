import getFullData from './components/main.js'

const RES_V_LIMIT = 5000

const IN_FILES_PATHS = [
    './src/c/inputData/a.in',
    './src/c/inputData/b.in',
    './src/c/inputData/c.in',
    './src/c/inputData/d.in',
    './src/c/inputData/e.in',
    './src/c/inputData/f.in',
]

const log = (...msg) => {
    console.log('>> js_log');
    console.log(...msg);
    console.log('--------');
}

let runFunction 
Module.onRuntimeInitialized = function() {
    runFunction = Module.cwrap('run', 'string', [])
}

const renderResult = ({ score, compiledFilesQ }) => {
    const resEl = document.getElementById('result')
    resEl.innerHTML = '' // remove childs
    const scoreEl = document.createElement('span')
    scoreEl.classList.add('score')
    const fileEl = document.createElement('span')
    scoreEl.textContent = `Score: ${score}`
    fileEl.textContent = `Compiled Files: ${compiledFilesQ}`
    resEl.appendChild(scoreEl)
    resEl.appendChild(fileEl)
}

const renderLoader = () => {
    const resEl = document.getElementById('result')
    resEl.innerHTML = '' // remove childs
    const dataVEl = document.getElementById('dataV')
    dataVEl.innerHTML = '' // remove childs
    const img = document.createElement('img')
    img.src = './src/images/geneticLoader.gif'
    img.alt = 'processing'
    img.classList.add('genLoader')
    resEl.appendChild(img)
}

const CF_MARGIN = 1

const renderVData = (servers) => {
    const resEl = document.getElementById('dataV')
    resEl.innerHTML = '' // remove childs
    servers.forEach(server => {
        const serverColEl = document.createElement('div')
        serverColEl.classList.add('serverCol')
        let totalH = 0
        log(server)
        server._order.forEach((name, i) => {
            const fileEl = document.createElement('div')
            fileEl.classList.add('compiledFile')
            fileEl.style.top = `${server[name].bt + i * CF_MARGIN}px`
            fileEl.style.height = `${server[name].ct - server[name].bt}px`
            fileEl.title = name
            totalH += server[name].ct - server[name].bt
            serverColEl.appendChild(fileEl)
        })
        serverColEl.style.height = `${totalH}px`
        resEl.appendChild(serverColEl)
    })
}

const runButton = document.getElementById('runButton')
runButton.onclick = () => {
    const inputSource = parseInt(document.getElementById('inputSource').value)
    const populationQ = parseInt(document.getElementById('populationQ').value) || 10
    const stagnationPeriod = parseInt(document.getElementById('stagnationPeriod').value || 15)
    const selectionQ = parseInt(document.getElementById('selectionQ').value || 5)
    const selectionPeriod = parseInt(document.getElementById('selectionPeriod').value || 5)
    runButton.classList.add('disabled')
    renderLoader()
    new Promise(res => {
        setTimeout(() => res(runFunction(inputSource, populationQ, stagnationPeriod, selectionQ, selectionPeriod)), 100)
    }).then((res) => {
        const resTokens = res.split('\n')
        const score = resTokens[0]
        const compiledFilesQ = resTokens[1]
        const data = resTokens.slice(2, -1).slice(0, RES_V_LIMIT)
        renderResult({ score, compiledFilesQ })
        runButton.classList.remove('disabled')

        const inFilePath = IN_FILES_PATHS[inputSource]
        getFullData(inFilePath, data).then(renderVData)
    })
}
