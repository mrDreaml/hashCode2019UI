const readFile = async path => await (await fetch(path)).text()

const parseData = str => {
    const lines = str.split('\n')
    const [filesQ, targetQ, serversQ] = lines[0].split(' ')
    const allFiles = {}
    const deps = {}
    let currentName
    for (let i = 1; i < lines.length; i++) {
        const line = lines[i]
        if (i <= +filesQ * 2) {
            if (i % 2 === 1) {
                const [name, ct, rt] = line.split(' ')
                currentName = name
                allFiles[currentName] = { ct: +ct, rt: +rt }
            } else {
                deps[currentName] = line.split(' ').slice(1)
            }
        }
        //skip target files
    }

    return {
        filesQ: +filesQ,
        targetQ: +targetQ,
        serversQ: +serversQ,
        allFiles,
        deps,
    }
}

const runSimulations = ({ serversQ, allFiles, deps, submitionResult }) => {
    const submitionResultMap = submitionResult.reduce((acc, line) => {
        const [name, serverId] = line.split(' ')
        acc[name] = serverId
        return acc
    }, {})
    const Servers = new Array(serversQ).fill().map(() => ({ _time: 0, _order: [] }))
    submitionResult.forEach(line => {
        const [name, serverId] = line.split(' ')
        const server = Servers[serverId]
        const calcedRT = deps[name].reduce((acc, depName) => {
            const depServerId = submitionResultMap[depName]
            if (depServerId !== serverId) {
                const depFile = Servers[depServerId][depName]
                const delta = depFile.ct + depFile.rt - server._time
                return delta < 0 ? 0 : delta
            }
            return acc
        }, 0)
        server[name] = {
            bt: server._time, // binding time
            ct: server._time + allFiles[name].ct, // ready compilation time
            rt: allFiles[name].rt, // replication time
        }
        server._order = server._order.concat(name)
        server._time += allFiles[name].ct
    })
    return Servers
}

export default async (filePath, submitionData) => {
    const res = await readFile(filePath)
    return runSimulations({ ...parseData(res), submitionResult: submitionData })
}