import {readFile, writeFile, mkdir} from 'fs/promises';

// read results
const data = await readFile("Result.txt", 'utf8')
const sets = data.split("______________ Set")
const parsedSets = sets.map(set => {
    set = set.split('\n').map(line => line.trim()).filter(line => line.length > 0)
    if (set.length < 5) return
    const pj = set[2].split('\t')
    const dj = set[4].split('\t')
    const expected = set.find(line => line.includes('Total')).split(' = ')[1]
    return {
        pj,
        dj,
        expected
    }
}).filter(Boolean)

// create CSV with Job,Pj,dj
const csvs = parsedSets.map(set => {
    const {pj, dj} = set
    const csv = "Job,Pj,dj\n" + pj.map((job, i) => `${i+1},${pj[i]},${dj[i]}`).join('\n')
    return csv
})

// mkdir
await Promise.all(parsedSets.map((set, i) => mkdir(`data/set_${i+1}`, {recursive: true})))

// write CSVs
await Promise.all(csvs.map((csv, i) => writeFile(`data/set_${i+1}/input.csv`, csv)))

// write expected
parsedSets.forEach((set, i) => {
    writeFile(`data/set_${i+1}/output.txt`, set.expected)
})