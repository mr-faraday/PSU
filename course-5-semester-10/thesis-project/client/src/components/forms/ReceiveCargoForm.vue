<script setup>
import { defineEmits, ref, defineExpose } from 'vue'
import { useToast } from 'vue-toastification'

const toast = useToast()
const emit = defineEmits(['submit'])

const clientId = ref('')
const weight = ref('')

const submitHandler = async (e) => {
  e.preventDefault()

  const cargoData = {
    clientId: Number(clientId.value),
    weight: Number(weight.value),
  }

  if (!cargoData.clientId || !cargoData.weight) {
    return toast.warning('Заполните все поля')
  }

  emit('submit', cargoData)
}

defineExpose({
  clearForm() {
    clientId.value = ''
    weight.value = ''
  },
})
</script>

<template>
  <form class="create-employee-form" @submit="submitHandler">
    <h4>Регистрация груза</h4>

    <div class="form-group">
      <input v-model="clientId" placeholder="ID клиента" type="number" />
    </div>

    <div class="form-group">
      <input v-model="weight" placeholder="Вес груза (кг)" type="number" />
    </div>

    <button type="submit">Зарегистрировать</button>
  </form>
</template>

<style lang="scss" scoped>
select {
  margin-bottom: 10px;
}
</style>
