<script setup>
import { defineEmits, ref, defineExpose } from 'vue'

const emit = defineEmits(['submit'])

const firstName = ref('')
const lastName = ref('')
const phone = ref('')

const submitHandler = async (e) => {
  e.preventDefault()

  const client = {
    firstName: firstName.value.trim(),
    lastName: lastName.value.trim(),
    phone: phone.value.trim(),
  }

  if (!client.firstName || !client.lastName || !client.phone) {
    return alert('Заполните все поля')
  }

  emit('submit', client)
}

defineExpose({
  clearForm() {
    firstName.value = ''
    lastName.value = ''
    phone.value = ''
  },
})
</script>

<template>
  <form class="create-employee-form" @submit="submitHandler">
    <h4>Регистрация клиента</h4>

    <div class="form-group">
      <input v-model="firstName" placeholder="Имя" />
    </div>

    <div class="form-group">
      <input v-model="lastName" placeholder="Фамилия" />
    </div>

    <div class="form-group">
      <input v-model="phone" placeholder="Телефон" />
    </div>

    <button type="submit">Зарегистрировать</button>
  </form>
</template>

<style lang="scss" scoped>
select {
  margin-bottom: 10px;
}
</style>
