/**
 * @type {{
 *   document_id: identity
 * }[]}
 */

const documents = [] // filled table ~700 rows

/**
 * @type {{
 *   extradition_id: identity
 *   extradion_date: timestamp,
 *   return_date: timestamp,
 *   document_id: identity
 * }[]}
 */
const extraditions = [] // emtpty table

const extraditionsQuantity = 14000
const fill = () => {
    const result = []

    for (let i = 1; i <= extraditionsQuantity; i++) {
        const extradition_date = Math.floor(Date.now() * Math.random()) // добавить начло для рандомной даты с 2002
        const returnedAt = extradition_date + Math.round(Math.random() * 1000 * 3600 * 24 * 365)
        const return_date = returnedAt > Date.now() ? null : returnedAt

        const pool = getAvailableDocuments(extradition_date, result)

        // if pool.length === 0 then fuck

        const { document_id } = pool[Math.floor(Math.random() * pool.length)]

        result.push({
            extradition_id: i,
            extradition_date,
            return_date,
            document_id
        })
    }

    extraditions.push(...result)
}

const getAvailableDocuments = (date, result) => {
    const currentlyInUse = result.filter(
        (i) => date > i.extradition_date && (!i.return_date || date < i.return_date)
    )

    // предусмотреть дату прибытия

    const unavailableDocuments = new Set(currentlyInUse.map((i) => i.document_id))

    return documents.filter((doc) => !unavailableDocuments.has(doc.document_id))
}

fill()
