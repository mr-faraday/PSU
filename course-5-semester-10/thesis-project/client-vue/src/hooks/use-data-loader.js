import { onMounted } from 'vue'
import { useDataFetch } from './use-data-fetch'

export function useDataLoader(fetchHandler, defaultValue) {
  const [loading, data, fetchData] = useDataFetch(fetchHandler, defaultValue)

  onMounted(fetchData)

  return [loading, data]
}
