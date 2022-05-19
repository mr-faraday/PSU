import { ref } from 'vue'

export function useDataFetch(fetchHandler, defaultValue) {
  const loading = ref(false)
  const data = ref(defaultValue)

  const fetchData = async () => {
    try {
      loading.value = true
      const res = await fetchHandler()

      data.value = res.data.result
    } catch (error) {
      data.value = defaultValue
      alert('Error')
    } finally {
      loading.value = false
    }
  }

  return [loading, data, fetchData]
}
